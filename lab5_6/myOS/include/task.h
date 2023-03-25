#ifndef __TASK_H__
#define __TASK_H__
typedef struct tskPara {
unsigned int priority;
unsigned int arrTime;
unsigned int exeTime;
} tskPara;
void initTskPara(tskPara *buffer);
void setTskPara(unsigned int option, unsigned int value, tskPara *buffer);
void getTskPara(unsigned int option, unsigned int *para, tskPara *buffer);
void tskEnd();
void tskStart();
#endif 