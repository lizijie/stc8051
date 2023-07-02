#ifndef MY_HEAD_H
#define MY_HEAD_H


/**
 * 
芯片型号：		STC89C52RC
系统频率: 		1.0592MHz
8051指令集: 	STC-Y1
*/


/**
 * 软件定时器，受限于各个芯片的性能差异，此软件定时并不精确。
 * @param ms 需要延时的毫秒时间
*/
void soft_delay(int ms);

#define _nop_() __asm NOP __endasm

#define SOFT_DEALY_1MS_INIT __data unsigned char delay_i, delay_j
#define SOFT_DELAY_1MS_RUN do { \
	_nop_(); \
	delay_i = 2; \
	delay_j = 199; \
	do \
	{ \
		while (--delay_j); \
	} while (--delay_i); \
} while(0)

void soft_delay(int ms) {
    int i = 0;
    SOFT_DEALY_1MS_INIT;
    for(i = 0; i < ms; ++i) {
        SOFT_DELAY_1MS_RUN;
    }
}

#endif