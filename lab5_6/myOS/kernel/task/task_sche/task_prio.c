void (*tick_hook)(void);
typedef struct tskPara {
unsigned int priority;
unsigned int arrTime;
unsigned int exeTime;
} tskPara;
typedef struct rdyque{
    unsigned int pid;
    tskPara Para;
    struct rdyque *next;
}rdyque;
int task_prio(unsigned int head){
    tick_hook=0;//关闭hook

    int max,cur_id;
    rdyque *tmp=head;
    max=tmp->Para.priority;
    cur_id=tmp->pid;
    while (tmp=tmp->next)
    {
        if(tmp->Para.priority>max){
            cur_id=tmp->pid;
            max=tmp->Para.priority;
        }
        
    }
    return cur_id;
}