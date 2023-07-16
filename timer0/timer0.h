#ifndef __TIMER0_H
#define __TIMER0_H

/**
 * 
芯片型号：		STC89C52RC
系统频率: 		1.0592MHz
8051指令集: 	STC-Y1
*/


#include "8052.h"
#include "stddef.h"

typedef void (*timer_callback) (void* ud);

timer_callback __time0_cb;
void* __time0_cb_ud;
int __time0_process = 0;
int __time0_process_max = 0;

int set_time0_cb(int ms, timer_callback cb, void* ud) {
	if (cb == NULL) {
		return -1;
	}

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
	
	__time0_cb = cb;
	__time0_cb_ud = ud;
	__time0_process = 0;
	__time0_process_max = ms;

	return 0;
}

void ___t0_timer_interrupt() __interrupt 1 {
	// 1ms
	TL0 = 0x66;	//设置定时初始值
	TH0 = 0xFC;	//设置定时初始值

	__time0_process = __time0_process + 1;
	if (__time0_process >= __time0_process_max) {
		__time0_process = 0;
		__time0_cb(__time0_cb_ud);
	}
}

#endif