#include "io.h"
#include "uart.h"

#define UART_PORT 0x3F8 // 串口端口号

/* 向串口输出一个字符
 * 使用封装好的 outb 函数 */
void uart_put_char(unsigned char ch) {
    outb(UART_PORT,ch);
}

// 向串口输出一个字符串
void uart_put_chars(char *str) {
    while(*str!='\0'){
        uart_put_char(*str);
        str++;
    }
}
