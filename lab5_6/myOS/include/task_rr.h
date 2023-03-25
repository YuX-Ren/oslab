#ifndef __TASKRR__
#define __TASKRR__
int cur_pid;
void sched();
void tskStart(unsigned int myTCBaddr);
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

#endif