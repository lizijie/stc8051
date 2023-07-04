#include "8052.h"
#include "utils.h"

void main() {
    while(1) {
        P1_0 = !P1_0 ;
        soft_sleep(1000);
        P1_0 = !P1_0;
        soft_sleep(1000);
    }

    while(1);
}