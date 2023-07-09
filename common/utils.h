#ifndef MY_HEAD_H
#define MY_HEAD_H

#include "8052.h"
#include "stdbool.h"
#include "stddef.h"

/**
 * 
芯片型号：		STC89C52RC
系统频率: 		1.0592MHz
8051指令集: 	STC-Y1
*/

#define _nop_() __asm NOP __endasm

void soft_sleep(int ms) {
	__data unsigned char i, j;

    int n = 0;
    for(n = 0; n < ms; ++n) {
        _nop_();
		i = 2;
		j = 199;
		do
		{
			while (--j);
		} while (--i);
    }
}



#define TIMER_LIST_MAX_SIZE 10

typedef void (*timer_callback) (int timer_id, void* ud);

struct timer_node {
	int timer_id; // timer标识ID
	int interval; // 每X毫秒触发定时器
	timer_callback cb;	// 触发定时器的处理函数
	void* ud; // 定时器处理函数，透传参数
	bool is_used;
	
	int process;
};


struct timer_node timer_list[TIMER_LIST_MAX_SIZE];
int cur_timer;

void init_timer_node(struct timer_node* node) {
	node->timer_id = 0;
	node->interval = 0;
	node->cb = NULL;
	node->is_used = 0;
	node->process = 0;
}

int init_timer() {
	// AUXR &= 0x7F;			//定时器时钟12T模式
	TMOD &= 0xF0;			//设置定时器模式
	TMOD |= 0x01;			//设置定时器模式

	// 1ms
	TL0 = 0x66;				//设置定时初始值
	TH0 = 0xFC;				//设置定时初始值

	TF0 = 0;				//清除TF0标志
	TR0 = 1;				//定时器0开始计时
	ET0 = 1;
	EA = 1;
	
	// 重置定时器列表
	cur_timer = 0;
	int i = 0;
	struct timer_node* node = NULL;
	for (i = 0; i < TIMER_LIST_MAX_SIZE; ++i) {
		init_timer_node(&timer_list[i]);
	}

	return 0;
}

int add_timer(int ms, timer_callback cb, void* ud) {
	if (cur_timer >= TIMER_LIST_MAX_SIZE) {
		return -1;	
	}
	
	struct timer_node* node = NULL;
	int i = 0;
	int idx = 0;
	for (i = 0; i < TIMER_LIST_MAX_SIZE; ++i) {
		idx = (cur_timer + i) % TIMER_LIST_MAX_SIZE;
		node = &timer_list[idx];
		if (node != NULL) {
			break;
		}
	}

	if (node == NULL) {
		return -2;
	}
	
	init_timer_node(node);
	node->timer_id = cur_timer;
	node->interval = ms;
	node->cb = cb;
	node->ud = ud;

	cur_timer = cur_timer + 1;

	return node->timer_id;
}

void del_timer(int timer_id) {
	if (timer_id < 0 || timer_id > TIMER_LIST_MAX_SIZE) {
		return;
	}

	struct timer_node* node = &timer_list[timer_id];
	if (node == NULL) {
		return;
	}

	node->is_used = 0;
}

void ___t0_timer_interrupt() __interrupt 1 {
	// 1ms
	TL0 = 0x66;	//设置定时初始值
	TH0 = 0xFC;	//设置定时初始值

	// TODO:
	// 1. 定时器排序
	// 2. 双timer_list交换
	// 3. itr->cb 异常处理

	int i =0;
	struct timer_node* itr = NULL;
	for (i = 0; i < TIMER_LIST_MAX_SIZE; ++i) {
		itr = &timer_list[i];
		if (itr->is_used == 1 && itr->cb != NULL) {
			itr->process = itr->process + 1;
			
			if (itr->process >= itr->interval){
				itr->cb(itr->timer_id, itr->ud);
				itr->process = 0;
			}
		}
	}

}

#endif