#ifndef __CTX_SW_H__
#define __CTX_SW_H__
void CTX_SW();
unsigned int prevTSK_StackPtrAddr;
unsigned int nextTSK_StackPtr;
void context_switch(unsigned int prevTskStkAddr, unsigned int nextTskStk) {
prevTSK_StackPtrAddr = prevTskStkAddr;
nextTSK_StackPtr = nextTskStk;
CTX_SW();
}


#endif 