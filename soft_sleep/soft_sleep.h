#ifndef __SOFT_SLEEP_H
#define __SOFT_SLEEP_H

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
#endif