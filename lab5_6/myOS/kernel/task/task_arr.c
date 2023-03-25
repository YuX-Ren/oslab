#include "../../include/task_arr.h"
#include "../../include/wallClock.h"
#include "../../include/kmalloc.h"
int tick_hook_arr(){
    extern int hh,mm,ss;
    static int tickles=0;
    tickles++;
    int flag;
    flag=0;
    if(!head) return;
    // if(tickles%20){
    while(head&&head->arrtime<hh*3600+mm*60+ss)
    {
        flag++;
        waitque *tmp=head;
        tskStart(&pool[head->pid]);
        head=head->next;
        kfree((unsigned long)tmp);
    }
    
    if(flag) sched();
    // }
}