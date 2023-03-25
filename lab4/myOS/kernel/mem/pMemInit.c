#include "../../include/myPrintk.h"
#include "../../include/mem.h"
#define uMemS 0x4000000
unsigned int pMemStart; //可用的内存的起始地址
unsigned int kMemSize,uMemSize,pMemSize;  //可用的大小
unsigned int kstart,ustart;



void memTest(unsigned long start, unsigned long grainSize){	
	unsigned short *p;
	unsigned short pdata;
	unsigned long addr;
	addr = start;
	pMemStart = start;
	pMemSize = 0;
	
	if (start < 0x100000 || grainSize < 4) return;  //检测是否越界和grainsize是否过小
	while (1) { 
	    //检测首两个字节
        p = (unsigned  short*) addr;
        pdata = *p;
        *p = 0xAA55;
        if (*p != 0xAA55 ) break;
        *p = 0x55AA;
        if (*p != 0x55AA ) break;
        *p = pdata;//复原
	    //检测末两个字节
        p = (unsigned  short*) (addr + grainSize - 2);
        pdata = *p;
        *p = 0xAA55;
        if (*p != 0xAA55 ) break;
        *p = 0x55AA;
        if (*p != 0x55AA ) break;
        *p = pdata;//复原
        //下一块
        pMemSize += grainSize;
        addr += grainSize;	
	}
     	
	myPrintk(0x7,"MemStart:@ %x  \n", pMemStart);
	myPrintk(0x7,"MemSize@  %x  \n", pMemSize);	
}

extern unsigned int _end;
void pMemInit(void)
{
  unsigned int _end_addr = (unsigned int)&_end;
  
  memTest(0x100000, 0x1000);
  myPrintk(0x7, "_end:  %x  \n", _end_addr);
  if (pMemStart <= _end_addr)
  {
    //init kernel
    kstart = _end_addr;
    kMemSize=uMemS-kstart;
    //init user
    ustart=uMemS;
    uMemSize=pMemSize-kMemSize;
  }
    //init kernel
  kMemHandler = dPartitionInit(kstart, kMemSize);
    //init user
  pMemHandler = dPartitionInit(ustart,uMemSize);
}