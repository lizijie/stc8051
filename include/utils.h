#ifndef MY_HEAD_H
#define MY_HEAD_H

#define _nop_() __asm NOP __endasm

// void Delay1ms()		//@11.0592MHz
// {
// 	__data unsigned char i, j;

// 	_nop_();
// 	_nop_();
// 	_nop_();
// 	i = 11;
// 	j = 190;
// 	do
// 	{
// 		while (--j);
// 	} while (--i);
// }


//@11.0592MHz
#define SOFT_DEALY_1MS_INIT __data unsigned char delay_i, delay_j

#define SOFT_DELAY_1MS_RUN do { \
	_nop_(); \
	_nop_(); \
	_nop_(); \
	delay_i = 11; \
	delay_j = 190; \
	do \
	{ \
		while (--delay_j); \
	} while (--delay_i); \
} while(0)

void soft_delay(int ms);

void soft_delay(int ms) {
    int i = 0;
    SOFT_DEALY_1MS_INIT;
    for(i = 0; i < ms; ++i) {
        SOFT_DELAY_1MS_RUN;
    }
}

#endif