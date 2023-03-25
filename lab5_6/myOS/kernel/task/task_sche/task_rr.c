#include "../../../include/task_rr.h"
int watchdog=-1;
unsigned int now=0;
int lastdog=-1;
void setwatchdog(int valid){
    lastdog=watchdog;
    if(valid==2){//暂停时间片后恢复
        watchdog=lastdog;
    }
    else{watchdog=valid;}
}//重置时间片和暂停时间片
void sched_tick(){

    static int ticks;//时间片记录
    if(watchdog==-1) return;
    if(watchdog==0) {ticks=0;}
    ticks++;
    if(!(ticks%2/*两次嘀嗒*/)){ 
        tskStart(&pool[cur_pid]);
        setwatchdog(0);
        sched();
    }
}
void (*tick_hook)(void);
int task_rr(unsigned int head){
    tick_hook=sched_tick;
    return *(unsigned int *) head;//返回头 ，采用遍历的方式分配时间片
}
