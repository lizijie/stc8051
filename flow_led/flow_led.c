#include "8052.h"
#include "utils.h"

void main() {
    while(1) {
        P1_0 = 1;
        soft_delay(1000);
        P1_0 = 0;
        soft_delay(1000);
    }
}