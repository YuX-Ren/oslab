#include "io.h"
#include "myPrintk.h"
#include "uart.h"
#include "vga.h"
#include "i8253.h"
#include "i8259A.h"
#include "tick.h"
#include "wallClock.h"

int strcmp(char *a,char *b){
        while((*a==*b)&&*a!='\0'){a++;b++;}
        return *a-*b;
}
// 字符串比较
int strcpy(char *a,char *b){
    while (*b!='\0'){
        *a=*b;
        a++;b++;
    }
}
//字符串拷贝
typedef struct myCommand {
    char name[80];
    char help_content[200];
    void (*func)(int argc, char (*argv)[8]);
}myCommand; 
int cmdnums=3;
myCommand all[];

int func_cmd(int argc, char (*argv)[8]){
    for(int i=0;i<cmdnums;i++){
        append2screen(all[i].name,0x04);
        append2screen("\x20",0x04);
    }
    append2screen("\n",0x04);
} 

// myCommand cmd={"cmd\0","List all command\n\0",func_cmd};

int func_help(int argc, char (*argv)[8]){
    for(int i=1;i<argc;i++){
        for(int j=0;j<cmdnums;j++){
            if(strcmp(argv[i],all[j].name)==0){append2screen(all[j].help_content,0x04);append2screen("\n",0x04);}
        }
    }
}
int func_hello(int argc, char (*argv)[8]){
    append2screen("Hello world\n",0x12);
}


myCommand all[100]={{"cmd\0","cmd:List all command",func_cmd},{"help\0","help:Usage: help [command]\nDisplay info about [command]",func_help},{"hello","hello:Hello world",func_hello}};
// 静态定义


int osCmdReg(char *name,char* help,void (*func)()){
            all[cmdnums].func=func;
            strcpy(all[cmdnums].name,name);
            strcpy(all[cmdnums].help_content,help);
            cmdnums++;
}
char *a="test";


//动态注册
void startShell(void){
    osCmdReg(a,a,func_hello);
//我们通过串口来实现数据的输入
    char BUF[256]; //输入缓存区
    int BUF_len=0;	//输入缓存区的长度
  
	int argc=0;
    char argv[8][8];
    do{
        BUF_len=0; 
        argc=0;
        myPrintk(0x07,"Student>>");
        while((BUF[BUF_len]=uart_get_char())!='\r'){
            uart_put_char(BUF[BUF_len]);//将串口输入的数存入BUF数组中
            BUF_len++;  //BUF数组的长度加
        }
        BUF[BUF_len]='\n';
        BUF[BUF_len+1]='\0';
        uart_put_chars(" -pseudo_terminal\n");
        uart_put_char('\r');
        append2screen(BUF,0x04);
        //向vga中输出伪终端内容
        for (int i = 0,k=0; i < BUF_len+1; i++)
        {   
            if((int)BUF[i]==32|BUF[i]=='\n'){
                argv[argc][k]='\0';
                argc++;
                k=0;
                continue;
            }           
            argv[argc][k]=BUF[i];
            k++;
        }
        // 参数处理
        for(int j=0;j<cmdnums;j++)
        {   
            if(strcmp(all[j].name,argv[0])==0){all[j].func(argc,argv);break;}
        }
        //命令调用  
    }while(1);

}

