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
unsigned long kstackalloc(){
    int flag=dPartitionAlloc(kMemHandler,0x1000)+0xF00;
    return flag;
}
unsigned long kstackfree(unsigned long stack){
    while (*(unsigned long*)stack!=0xFFFFFFFF)
    {
        stack+=4;
    }
    
    return dPartitionFree(kMemHandler,stack-0xF00);
}
unsigned long kfree(unsigned long start){

    return dPartitionFree(kMemHandler,start);
}