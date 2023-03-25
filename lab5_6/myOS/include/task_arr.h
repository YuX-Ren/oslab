#ifndef __TASKARR_H__
#define __TASKARR_H__
typedef struct tskPara {
unsigned int priority;
unsigned int arrTime;
unsigned int exeTime;
} tskPara;
typedef struct myTCB{
    unsigned int pid;
    unsigned int state;
    unsigned int stack;
    tskPara para;
}myTCB;
myTCB pool[];
void  tskStart(unsigned int myTCB);
typedef struct waitque
{
    unsigned int pid;
    unsigned int arrtime;
    struct waitque *next;
}waitque;
void sched();
waitque* head;
waitque* tail;
#endif