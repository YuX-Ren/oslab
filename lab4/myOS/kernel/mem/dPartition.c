#include "../../include/myPrintk.h"

// dPartition 是整个动态分区内存的数据结构
typedef struct dPartition
{
	unsigned int size;
	unsigned int firstFreeStart;
} dPartition; //共占8个字节

#define dPartition_size ((unsigned int)0x8)

void showdPartition(struct dPartition *dp)
{
	myPrintk(0x5, "dPartition(start=0x%x, size=0x%x, firstFreeStart=0x%x)\n", dp, dp->size, dp->firstFreeStart);
}

// EMB每一个block的数据结构，userdata可以暂时不用管。
typedef struct EMB
{
	unsigned int size;
	union
	{
		unsigned int nextStart; // if free: pointer to next block
		unsigned int userData;	// if allocated, blongs to user
	};
} EMB; //共占8个字节

#define EMB_size ((unsigned int)0x8)

void showEMB(struct EMB *emb)
{
	myPrintk(0x3, "EMB(start=0x%x, size=0x%x, nextStart=0x%x)\n", emb, emb->size, emb->nextStart);
}

unsigned int dPartitionInit(unsigned int start, unsigned int totalSize)
{	
	//初始化句柄
	*(unsigned int *)start = totalSize;
	*(unsigned int *)(start + 4) = start + 8;
	//初始化第一块EMB
	*(unsigned int *)(start + 8) = totalSize - 12; 
	*(unsigned int *)(start + 12) = 0;
	return start;
}

void dPartitionWalkByAddr(unsigned int dp)
{
	showdPartition(dp);
	EMB *emb;
	emb = *(EMB **)(dp + 4);
	while (emb)
	{
		showEMB(emb);
		emb = (EMB *)emb->nextStart;
	}
}

//=================firstfit, order: address, low-->high=====================
/**
 * return value: addr (without overhead, can directly used by user)
 **/

unsigned int dPartitionAllocFirstFit(unsigned int dp, unsigned int size)
{
	EMB *emb, *pre, *cur;
	unsigned int alignS;
	emb = *(EMB **)(dp + 4);
	if(!emb) return 0;

	// 4字节对齐
	alignS = size % 4 ? (size / 4 * 4 + 8) : size + 4;


	if (alignS + 8 > *(unsigned int *)dp)
		{return 0;}//如果内存过大return
	while (emb->size < (alignS - 4))
	{
		pre = emb;
		emb = (EMB *)emb->nextStart;
		if (!emb) return 0; //未找到满足要求的EMB
	}

	//第一块满足
	if (emb == *(EMB **)(dp + 4))
	{
		if (emb->size == (alignS - 4))
		{
			*(unsigned int *)dp = -emb->nextStart + *(unsigned int *)(dp + 4) + *(unsigned int *)dp;
			(*(unsigned int *)(dp + 4)) = emb->nextStart;
		}
		else
		{
			*(unsigned int *)dp = *(unsigned int*)dp-alignS;
			(*(unsigned int *)(dp + 4)) += alignS;
			cur = *(EMB **)(dp + 4);
			cur->size = emb->size - alignS;
			cur->nextStart = emb->nextStart;
		}
	}

	//EMB正好满足
	else if ((alignS - 4) == emb->size)
	{
		pre->nextStart = emb->nextStart;
	}

	//一般
	else
	{
		pre->nextStart = (unsigned int)emb + alignS;
		*(unsigned int *)(pre->nextStart) = emb->size - alignS;
		*(unsigned int *)(pre->nextStart + 4) = emb->nextStart;
	}

	emb->size = alignS - 4;
	return (unsigned int)emb + 4;
}

unsigned int dPartitionFreeFirstFit(unsigned int dp, unsigned int start)
{
	start -= 4;
	unsigned int end = start + (*(unsigned int *)start) + 4;
	//边界条件
	if (end >= *(unsigned int *)dp + *(unsigned int *)(dp+4)-8 ||  start < dp + 8)
		return 0;

	//第一块空闲块前
	if (end < *(unsigned int *)(dp + 4))
	{
		*(unsigned int *)(start + 4) = *(unsigned int *)(dp + 4);
		*(unsigned int *)dp+=(*(unsigned int *)(dp+4)-start);
		*(unsigned int *)(dp + 4) = start;
		return 1;
	}
	if (end == *(unsigned int *)(dp + 4))
	{
		*(unsigned int *)(dp + 4) = start;
		*(unsigned int *)dp +=*(unsigned int *) start+4;
		*(unsigned int *)start = *(unsigned int *)end + 4 + *(unsigned int *)start;
		*(unsigned int *)(start + 4) = *(unsigned int *)(end + 4);
		
		return 1;
	}



	EMB *pre;
	EMB *emb = *(EMB **)(dp + 4);
	//遍历找到释放块前后块
	while (start > (unsigned int)emb && (unsigned int)emb)
	{
		pre = emb;
		emb = (EMB *)(emb->nextStart);
	}

	//被释放为最后一块
	if (emb == 0)
	{
		if ((unsigned int)pre + pre->size + 4 == start)
		{
			pre->size = pre->size + 4 + *(unsigned int *)start;
			return 1;
		}
		else
		{
			pre->nextStart = start;
			*(unsigned int *)(start + 4) = 0;
		}
	}


	else
	{
		int flag = 0;
		//基于flag实现块的链接，寻找时只需进行合并操作

		//integrate
		if ((unsigned int)emb == end)//2-3
		{
			(*(unsigned int *)start) += (4 + emb->size);
			flag += 1;
		}
		if ((unsigned int)pre + pre->size + 4 == start)//1-2
		{
			pre->size = pre->size + 4 + *(unsigned int *)start;
			flag += 2;
		}
		//link
		switch (flag)
		{
		case 1://2-3
			*(unsigned int *)(start + 4) = emb->nextStart;
			break;
		case 2://1-2
			break;
		case 3://1-2-3
			pre->nextStart = emb->nextStart;
			break;
		default:
			pre->nextStart = start;
			*(EMB **)(start + 4) = emb;
			break;
		}
	}
	return 1;
}

unsigned int dPartitionAlloc(unsigned int dp, unsigned int size)
{
	return dPartitionAllocFirstFit(dp, size);
}

unsigned int dPartitionFree(unsigned int dp, unsigned int start)
{
	return dPartitionFreeFirstFit(dp, start);
}
