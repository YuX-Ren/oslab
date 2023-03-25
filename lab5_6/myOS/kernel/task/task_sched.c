#include "../../include/ctx_sw.h"
#include "../../include/task_sched.h"
#include "../../include/irq.h"
#include "../../include/myPrintk.h"
#include "../../include/kmalloc.h"
#define FIFO 0
#define PRIO 1
#define rr 2
#define sjf 3
#define NULL 0

int sched_num=0;
rdyque *RDQtail=NULL;
rdyque *RDQhead=NULL;
int cur_pid;//记录单前pid
void sched();
//任务进入运行将其从就绪队列中调出
void queout(int pid){
    rdyque *pre;
    rdyque *cur=RDQhead;// 双指针维护链表
    if(cur->pid==pid) {
        RDQhead=RDQhead->next;
        kfree(cur);//销毁当前链表空间
        return;
    }//在头部
    for (; cur; pre=cur,cur=cur->next)
    {
        if(cur->pid==pid) break;
    }//遍历链表
    if(!cur) while (1)
    {
        myPrintk(0x4,"rdyque error");
    }//如果没有异常
    pre->next=cur->next;
    kfree(cur);//销毁当前链表空间
}
void setSysScheduler(unsigned int what)
{
    sched_num=what;
}// 设置调度算法
void tskStart(unsigned int myTCBaddr){
    myTCB *tmp=(myTCB *)(myTCBaddr);
    if(RDQhead==NULL){
        RDQtail=RDQhead=(rdyque *)(kalloc(sizeof(rdyque)));
        RDQhead->Para=tmp->para;
        RDQhead->pid=tmp->pid;
        RDQhead->next=NULL;
        tmp->state=1;
    }//若就绪队列为空，初始化
    else{
    RDQtail->next=(rdyque *)(kalloc(sizeof(rdyque)));
    RDQtail=RDQtail->next;
    RDQtail->Para=tmp->para;
    RDQtail->pid=tmp->pid;
    RDQtail->next=NULL;
    tmp->state=1;
    }//在尾部插入链表
}
void tskEnd(){
    if(sched_num==rr) {
        disable_interrupt();
        setwatchdog(0);
        enable_interrupt();
        }// 如果是轮询算法 重置时间片并关闭
    destroyTsk(cur_pid);//将进程归还进程池
    sched();//进入调度
}
unsigned int * pre_stackAddr;
unsigned int * cur_stackAddr;
void sched(){
    if(!RDQhead) {
        cur_stackAddr=pre_stackAddr;
        pre_stackAddr=&pool[0].stack;//将当前栈存入前一个栈，用作下一任务的前一个栈
        context_switch(cur_stackAddr,pool[0].stack);
    }//如果就绪队列空，进入shell
    switch (sched_num)
    {
    case FIFO :
        cur_pid=task_fifo(RDQhead);    
        break;
    case PRIO :
        cur_pid=task_prio(RDQhead);
    break;
    case rr :
        cur_pid=task_rr(RDQhead);
    break;
    // case sjf :
    //     cur_pid=task_sjf(RDQhead);
    // break;
    }// 根据不同算法活得当前运行pid
    queout(cur_pid);//调出readyque
    cur_stackAddr=pre_stackAddr;
    pre_stackAddr=&pool[cur_pid].stack;//将当前栈存入前一个栈，用作下一任务的前一个栈
    setwatchdog(1);//分配时间片，其他算法不会收到影响
    context_switch(cur_stackAddr,pool[cur_pid].stack);
}