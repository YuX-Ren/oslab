// #include 
#include "../../include/wallClock.h"
#define PRIORITY 1
#define EXETIME 2
#define ARRTIME 3
typedef struct tskPara {
unsigned int priority;
unsigned int arrTime;
unsigned int exeTime;
} tskPara;
void initTskPara(tskPara *buffer){
    extern int hh,mm,ss;
    static int counter=0;
    buffer->priority=++counter;//将优先级与调入顺序设成相反
    buffer->arrTime=hh*3600+mm*60+ss+1;//到达时间 位当前时间加一
    buffer->exeTime=100;//100 ticks 100ms
}
void setTskPara(unsigned int option, unsigned int value, tskPara *buffer){
    switch (option)
    {
    case PRIORITY:
        buffer->priority=value;
        break;
    case EXETIME:
        buffer->exeTime=value;
    case ARRTIME:
        buffer->arrTime=value;
        break;
    }
}
void getTskPara(unsigned int option, unsigned int *para, tskPara *buffer){
    switch (option)
    {
    case PRIORITY:
        *para= buffer->priority;
        break;
    case EXETIME:
        *para= buffer->exeTime;
    case ARRTIME:
        *para= buffer->arrTime;
        break;
    }
}