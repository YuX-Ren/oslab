void (*tick_hook)(void);
int task_fifo(unsigned int head){
tick_hook=0;//关闭hook
return *(unsigned int *) head;
}
