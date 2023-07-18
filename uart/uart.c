#include "8052.h"
#include "uart.h"
#include "soft_sleep.h"
#include "def.h"

void uart_read() interrupt 4 {
    // RI 与 TI都会触发中断4，所以中断4处理函数中要区分RI和TI
    if (RI == 1) {
        P1_0 = !P1_0;
        RI = 0;
    }
}

int main() {
    uart_init();

    while(1){
        uart_write(0x12);
        soft_sleep(1000);
    }
    return 0;
}