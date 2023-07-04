#ifndef MY_HEAD_H
#define MY_HEAD_H

#include "8052.h"

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



#define TIMER_LIST_SIZE 10

typedef void (*timer_callback) (void* ud);

struct timer_node {
	int timer_id; // timer标识ID
	int interval; // 每X毫秒触发定时器
	timer_callback cb;	// 触发定时器的处理函数
	
	int interval_process;
};


struct timer_node timer_list[TIMER_LIST_SIZE];

int t0_count;
int t0_count_target;

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
}

int add_timer(int ms) {
	
	t0_count = 0;
	t0_count_target = ms;
}

void t0_timer() __interrupt 1 {
	TL0 = 0x66;				//设置定时初始值
	TH0 = 0xFC;				//设置定时初始值
	t0_count = t0_count + 1;
	if (t0_count >= t0_count_target) {
		t0_count = 0;
		P1_0 = !P1_0;
	}
}

#endif