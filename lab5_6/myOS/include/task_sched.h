#ifndef __TASK_SCHED_H__
#define __TASK_SCHED_H__
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
extern myTCB pool[10];
typedef struct rdyque{
    unsigned int pid;
    tskPara Para;
    struct rdyque *next;
}rdyque;
int task_fifo(unsigned int head);
int task_prio(unsigned int head);
int task_rr(unsigned int head);
int task_sjf(unsigned int head);
void destroyTsk(int tskIndex);
#endif 