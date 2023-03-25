#include "io.h"
#include "vga.h"

#define VGA_BASE 0xB8000 // vga 显存起始地址
#define VGA_END  0xB8F00 // vga 显存结束地址
#define VGA_LAST_LINE  0xB8E60 //vga 显存倒数第一行
#define VGA_SCREEN_WIDTH 80 // vga 屏幕宽度（可容纳字符数）
#define VGA_SCREEN_HEIGHT 25 // vga 屏幕高度

#define CURSOR_LINE_REG 0xE // 高八位
#define CURSOR_COL_REG 0xF // 低八位
#define CURSOR_INDEX_PORT 0x3D4 // 光标行列索引端口号
#define CURSOR_DATA_PORT 0x3D5 // 光标数据端口号


/* 将光标设定到特定位置
 * 提示：使用 outb */
void set_cursor_pos(unsigned int pos) {
    outb(CURSOR_INDEX_PORT,0xE);
    outb(CURSOR_DATA_PORT,(pos>>8));//设定高八位
    outb(CURSOR_INDEX_PORT,0xF);
    outb(CURSOR_DATA_PORT,(pos&0xFF));//设定低八位
}

/* 获取光标当前所在位置
 * 提示：使用 inb */ 
unsigned int get_cursor_pos(void) {
    int unsigned pos;
    outb(CURSOR_INDEX_PORT,0xE);
    pos=(inb(CURSOR_DATA_PORT)<<8);
    outb(CURSOR_INDEX_PORT,0xF);
    pos+=(inb(CURSOR_DATA_PORT));
    return pos;
}

/* 滚屏，vga 屏幕满时使用。丢弃第一行内容，将剩余行整体向上滚动一行
 * 提示：使用指针修改显存 */
void scroll_screen(void) {
    unsigned long int* cl=(unsigned long int*)VGA_BASE;
    do{
            *cl=*(cl+40);
    }while((int)(cl++)!=VGA_LAST_LINE);
    cl=(unsigned long int*)VGA_LAST_LINE;
    do{*cl=0x0F000F00;}while((int)(cl+=1)!=VGA_END);
}
//最后一行移入上一行后 设置初始态 foreground 白 background 黑

/* 向 vga 的特定光标位置 pos 输出一个字符
 * 提示：使用指针修改显存 */
void put_char2pos(unsigned char c, int color, unsigned int pos) {
    short int *p; 
    p=(short int *)(pos*2+0xB8000);//活得指向显存指针
    *p=(short int)c+(color<<8);
}
//基于偏移和基址写入两字节 short 

/* 清除屏幕上所有字符，并将光标位置重置到顶格
 * 提示：使用指针修改显存 */
void clear_screen(void) {
    unsigned long int* cl=(unsigned long int*)VGA_BASE;
    do{*cl=0x0F000F00;}while((int)(cl+=1)!=VGA_END);
    set_cursor_pos(0);
}
//为所有显存设置初值 foreground 白 background 黑

/* 向 vga 的当前光标位置输出一个字符串，并移动光标位置到串末尾字符的下一位
 * 如果超出了屏幕范围，则需要滚屏
 * 需要能够处理转义字符 \n */
void append2screen(char *str, int color) { 
    unsigned int pos=get_cursor_pos();
    while (*str!='\0')
    {
        if(*str=='\n'){
            if(pos>=(VGA_LAST_LINE-0xB8000)/2){scroll_screen();pos=(VGA_LAST_LINE-0xB8000)/2;}
            else{pos=(pos/80+1)*80;}
            str++;
            continue;
        }
        else{put_char2pos(*str,color,pos);}
        str++;
        pos+=1;
        if(pos==(VGA_END-0xB8000)/2){scroll_screen();pos=((VGA_LAST_LINE-0xB8000)/2);}
    }
    //滚屏后修改pos值于此处判断并进行
    set_cursor_pos(pos);
}