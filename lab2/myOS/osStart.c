#include "vga.h"
#include "myPrintk.h"

/* 此文件无需修改 */

// 用户程序入口
void myMain(void);

void put_char2pos(unsigned char c, int color, unsigned short int pos);
void osStart(void) {
    clear_screen();
    put_char2pos('c', 0x7, 0);
    myMain();
    while(1); 
}
