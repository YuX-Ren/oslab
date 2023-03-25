#include "../../include/task.h"
#include "../../../userApp/shell.h"
#include "../../include/kmalloc.h"
#include "../../include/myPrintk.h"
// #include "../"
#define NULL 0
#define IDLE 0
typedef struct myTCB{
    unsigned int pid;
    unsigned int state;
    unsigned int stack;
    tskPara para;
}myTCB;
myTCB pool[10];
int ready[10];

typedef struct waitque
{
    unsigned int pid;
    unsigned int arrtime;
    struct waitque* next;
}waitque;

waitque* head=NULL;
waitque* tail=NULL;

int findready(){
    int i=0;
    for(;ready[i]==0&i<10;i++);
    ready[i]=0; 
    return i;
}// 基于位图在进程池中找到可用进程
void stack_init(unsigned int **stk, void (*task)(void)) {
*(*stk)-- = (unsigned int)0xFFFFFFFF; //栈底 kfree 基于此 free
*(*stk)-- = (unsigned int)tskEnd; // CS
*(*stk)-- = (unsigned int)task; // eip
// pushf
*(*stk)-- = (unsigned int)0x0202; // flag registers
// pusha
*(*stk)-- = (unsigned int)0xAAAAAAAA; // eax
*(*stk)-- = (unsigned int)0xCCCCCCCC; // ecx
*(*stk)-- = (unsigned int)0xDDDDDDDD; // edx
*(*stk)-- = (unsigned int)0xBBBBBBBB; // ebx
*(*stk)-- = (unsigned int)0x44444444; // esp
*(*stk)-- = (unsigned int)0x55555555; // ebp
*(*stk)-- = (unsigned int)0x66666666; // esi
**stk = (unsigned int)0x77777777; // edi
}

void createTsk(void (*tskBody)(void)){
    int cur_id=findready();//寻找可用在进程池中
    waitque *cur;
    pool[cur_id].pid=cur_id;
    pool[cur_id].state=0;
    pool[cur_id].stack=kstackalloc();// 调用专门的栈空间维护函数
    stack_init(&pool[cur_id].stack,tskBody);
    initTskPara(&pool[cur_id].para);//初始化到达时间等参数
    if(head==NULL){
        tail=head=(waitque*)kalloc(sizeof(waitque));
        head->pid=cur_id;
        head->next=NULL;
        head->arrtime=pool[cur_id].para.arrTime;
        return;
    }// 如果等待队列为空 初始化链表
    else{
        cur=(waitque*)kalloc(sizeof(waitque));
        cur->pid=cur_id;
        cur->next=NULL;
        cur->arrtime=pool[cur_id].para.arrTime;
        tail->next=cur;
        tail=tail->next;
        return;
    }//在尾部插入新任务链表
}

void destroyTsk(int tskIndex){
    ready[tskIndex]=1;//重置位图
    pool[tskIndex].state=-1;
    kstackfree (pool[tskIndex].stack);//销毁栈空间
}
void initskbody(){
    for(int i=0;i<10;i++){ready[i]=1;}//初始化进程池
    int cur_id=findready();//寻找可用在进程池中
    pool[cur_id].pid=cur_id;
    pool[cur_id].state=0;
    pool[cur_id].stack=kstackalloc();// 分配两倍的必须栈大小，函数跳转时会向栈中写入 pc
    stack_init(&pool[cur_id].stack,startShell);// 初始化shell任务
}