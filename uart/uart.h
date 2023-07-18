#ifndef __UART_H
#define __UART_H

/*
芯片型号：		STC89C52RC
系统频率: 		11.0592MHz
8051指令集: 	STC-Y1
*/

#include "8052.h"


int uart_init(){
    //2400bps@11.0592MHz

    // uart寄存器置位
    SM0 = 0;
    SM1 = 1; // 工作方式1
    REN = 1; // 同时打开发送/接收器
    PCON &= 0x0F; // 选用晶振为11.0592MHz, 不需要SMOD=0加倍波特率
    TI = 0; // 重置发送器
    RI = 0; // 重置接收器


    // 定时器1寄存器置位
	TMOD &= 0x0F;			//设置定时器模式
	TMOD |= 0x20;			//设置定时器模式，串口工作一定要8位自动重装模式
	TL1 = 0xF4;			//设置定时初始值
	TH1 = 0xF4;			//设置定时重载值
	TF1 = 0;				//清除TF1标志
	TR1 = 1;				//定时器1开始计时
	ET1 = 0;                //禁止定时器中断

    EA = 1; // 打开全局中断
    ES = 1; // 打开串口中断

    return 0;
}

void uart_write(char data) {
    SBUF = data;
    while(TI == 0);
    TI = 0;
}

#endif