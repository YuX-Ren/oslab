#include "io.h"
#define clkfrq 1193180/100 
void init8253(void){
    // set 8253 timer-chip
    outb(0x43, 0x34);
    outb(0x40,clkfrq % 256);
    outb(0x40, clkfrq / 256);

}
