#include "8052.h"
#include "utils.h"

void timer_cb(void* ud) {
    
}

void main() {
    int user_data = 1;
    int timer_id = add_timer(1000, timer_cb, (void*)&user_data);
    if (timer_id <= 0) {
        // TODO: add timer fail.
        return;
    }


    while(1);

    del_timer(timer_id);
}