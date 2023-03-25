#include "../../include/myPrintk.h"
// 一个EEB表示一个空闲可用的Block
typedef struct EEB {
	unsigned int next_start;
}EEB;	//占4个字节

#define EEB_size 4

void showEEB(struct EEB *eeb){
	myPrintk(0x7,"EEB(start=0x%x, next=0x%x)\n", eeb, eeb->next_start);
}

//eFPartition是表示整个内存的数据结构
typedef struct eFPartition{
	unsigned int totalN;	//所有EEB（整个EEB包含隔离区）
	unsigned int perSize;  //unit: byte	EEB实际可用的内存
	unsigned int firstFree;
}eFPartition;	//占12个字节

#define eFPartition_size 12

void showeFPartition(struct eFPartition *efp){
	myPrintk(0x5,"eFPartition(start=0x%x, totalN=0x%x, perSize=0x%x, firstFree=0x%x)\n", efp, efp->totalN, efp->perSize, efp->firstFree);
}

void eFPartitionWalkByAddr(unsigned int efpHandler){
	//本函数需要实现！！！
	/*功能：本函数是为了方便查看和调试的。
	1、打印eFPartiiton结构体的信息，可以调用上面的showeFPartition函数。
	2、遍历每一个EEB，打印出他们的地址以及下一个EEB的地址（可以调用上面的函数showEEB）

	*/
	EEB * eeb=*(EEB **)(efpHandler+8);
	showeFPartition(efpHandler);
	while (eeb)
	{
		showEEB(eeb);
		eeb=(EEB *)eeb->next_start;
	}
	
}


unsigned int eFPartitionTotalSize(unsigned int perSize, unsigned int n){
	return n*(perSize+4)+eFPartition_size;
}

unsigned int eFPartitionInit(unsigned int start, unsigned int perSize, unsigned int n){
	//4字节对齐
	perSize=(perSize+3)/4*4;
	//初始化句柄
	*(unsigned int *)start=eFPartitionTotalSize(perSize,n);
	*(unsigned int *)(start+4)=perSize;
	
	//初始化EEB描述字
	*(unsigned int *)(start+8)=start+12;
	for(int i=0;i<n-1;i++){
		*(unsigned int *)(start+12+i*(perSize+4))=start+12+(i+1)*(perSize+4);
	}
	return start;
}

unsigned int  eFPartitionAlloc(unsigned int EFPHandler)
{
  EEB *eeb;
  if ( ! *(unsigned int *)(EFPHandler + 8) )return 0;//如果句柄无效return
  
  eeb = *(EEB **)(EFPHandler + 8);
  *(unsigned int *)(EFPHandler + 8) = eeb->next_start;
  return (unsigned int)eeb +4; 
}


unsigned int eFPartitionFree(unsigned int EFPHandler,unsigned int mbStart){
if(mbStart<EFPHandler+16)return 0;//如果越界 return
int a=((mbStart-4)-EFPHandler-12)%(*(unsigned int *)(EFPHandler+4)+4);
if(a) return 0;//判断start地址是否正确（EEB头地址）
*(unsigned int *)(mbStart-4)=*(unsigned int *)(EFPHandler+8);
*(unsigned int *)(EFPHandler+8)=mbStart-4;
return 1;
}
