#include "../myOS/userInterface.h"
#include "shell.h"
#include "../myOS/include/kmalloc.h"
#define FIFO 0
#define PRIO 1
#define rr 2
#define sjf 3
#include "../myOS/include/task_arr.h"
int do_some_calcultaion(){
    int n=1000;
    int count=0, i,j;
    int *nums=kalloc(n*4);
    for(int k=0;k<n;k++){
        nums[k]=0;
    }
    for(i = 2;i*i<=n;i++)
    {
        if(!nums[i]){
            for(j = i*i;j<n;j+=i){
                nums[j] = 1;
            }
        }
    }
    for(i = 2 ; i < n ; i++){
        if(!nums[i]) count++;
    }
    return count;
}
int aaa(){
    Printf(0x8,"aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa\n");
}
int test_a(){
    aaa();
    int answer ;
    myPrintf(0x6,"******************************\nNow Enter A\n******************************\n");
        int n=1000;
    int count=0, i,j;
    int *nums=kalloc(n*4);
    for(int k=0;k<n;k++){
        nums[k]=0;
    }
    for(i = 2;i*i<=n;i++)
    {
        if(!nums[i]){
            for(j = i*i;j<n;j+=i){
                nums[j] = 1;
            }
        }
    }
    for(i = 2 ; i < n ; i++){
        if(!nums[i]) count++;
    }
    // answer=do_some_calcultaion();
    // myPrintf(0x6,"A:answer is %d\n",answer);
    myPrintf(0x6,"A:answer is %d\n",count);
}
int test_b(){
    aaa();
    int answer ;
    myPrintf(0x6,"******************************\nNow Enter B\n******************************\n");
    int n=1000;
    int count=0, i,j;
    int *nums=kalloc(n*4);
    for(int k=0;k<n;k++){
        nums[k]=0;
    }
    for(i = 2;i*i<=n;i++)
    {
        if(!nums[i]){
            for(j = i*i;j<n;j+=i){
                nums[j] = 1;
            }
        }
    }
    for(i = 2 ; i < n ; i++){
        if(!nums[i]) count++;
    }
    // answer=do_some_calcultaion();
    // myPrintf(0x6,"B:answer is %d\n",answer);
    myPrintf(0x6,"B:answer is %d\n",count);

}
int test_c(){
    aaa();
    int answer ;
    myPrintf(0x6,"******************************\nNow Enter C\n******************************\n");
    int n=1000;
    int count=0, i,j;
    int *nums=kalloc(n*4);
    for(int k=0;k<n;k++){
        nums[k]=0;
    }
    for(i = 2;i*i<=n;i++)
    {
        if(!nums[i]){
            for(j = i*i;j<n;j+=i){
                nums[j] = 1;
            }
        }
    }
    for(i = 2 ; i < n ; i++){
        if(!nums[i]) count++;
    }
    // answer=do_some_calcultaion();
    // myPrintf(0x6,"C:answer is %d\n",answer);
    myPrintf(0x6,"C:answer is %d\n",count);

}
int a(){
    Printf(0x3,"this a task\n");
}
int b(){
    Printf(0x3,"this b task\n");
}
int c(){
    Printf(0x3,"this c task\n");
}
int aa(){
    Printf(0x3,"this aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa task\n");
    Printf(0x3,"this aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa task\n");
    Printf(0x3,"this aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa task\n");
    Printf(0x3,"this aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa task\n");
    Printf(0x3,"this aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa task\n");
    Printf(0x3,"this aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa task\n");
    Printf(0x3,"this aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa task\n");
    Printf(0x3,"this aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa task\n");
}
int bb(){
    Printf(0x4,"this bbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbb bbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbb task\n");
    Printf(0x4,"this bbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbb bbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbb task\n");
}
int cc(){
    Printf(0x5,"this cccccccccccccccccccccccccccccccccccccc cccccccccccccccccccccccccccccccccccccc task\n");
    Printf(0x5,"this cccccccccccccccccccccccccccccccccccccc cccccccccccccccccccccccccccccccccccccc task\n");
}
int testfifo(){
    setSysScheduler(FIFO);
    createTsk(test_a);
        Printf(3,"init test_a\n");
    createTsk(test_b);
        Printf(3,"init test_b\n");
    createTsk(test_c);
        Printf(3,"init test_c\n");
}
int fifotest(){
    setSysScheduler(FIFO);
    createTsk(a);
    Printf(3,"init a\n");
    createTsk(b);
        Printf(3,"init b\n");
    createTsk(c);
        Printf(3,"init c\n");
}
int testprio(){
    setSysScheduler(PRIO);
    createTsk(test_a);
        Printf(3,"init test_a\n");
    createTsk(test_b);
        Printf(3,"init test_b\n");
    createTsk(test_c);
        Printf(3,"init test_c\n");
}
int priotest(){
    setSysScheduler(PRIO);
    createTsk(a);
    Printf(3,"init a\n");
    createTsk(b);
        Printf(3,"init b\n");
    createTsk(c);
        Printf(3,"init c\n");
}
int RRtest(){
    setSysScheduler(rr);
    createTsk(aa);
    Printf(3,"init aa\n");
    createTsk(bb);
        Printf(3,"init bb\n");
    createTsk(cc);
        Printf(3,"init cc\n");
}
int testRR(){
    setSysScheduler(rr);
    createTsk(test_a);
        Printf(3,"init test_a\n");
    createTsk(test_b);
        Printf(3,"init test_b\n");
    createTsk(test_c);
        Printf(3,"init test_c\n");
}
#define NULL (void*)0
void taskTestCaseInit(void){
    addNewCmd("testfifo",testfifo,NULL,"fifotest");
    addNewCmd("testprio",testprio,NULL,"priotest");
    addNewCmd("fifotest",fifotest,NULL,"testfifo");
    addNewCmd("priotest",priotest,NULL,"testprio");
    addNewCmd("RRtest",RRtest,NULL,"testRR");
    addNewCmd("testRR",testRR,NULL,"RRtest");

}