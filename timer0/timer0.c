#include "8052.h"
#include "timer0.h"

void timer_cb(void* ud) {
    P1_0 = !P1_0;
}

void main() {
    set_time0_cb(1000, timer_cb, NULL);
    
    while(1);
}