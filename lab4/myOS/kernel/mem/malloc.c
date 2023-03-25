#include "../../include/mem.h"
//user
unsigned long malloc(unsigned long size){

    return dPartitionAlloc(pMemHandler,size);

}

unsigned long free(unsigned long start){

    return dPartitionFree(pMemHandler,start);
}

//kernel
unsigned long kalloc(unsigned long size){

    return dPartitionAlloc(kMemHandler,size);

}

unsigned long kfree(unsigned long start){

    return dPartitionFree(kMemHandler,start);
}