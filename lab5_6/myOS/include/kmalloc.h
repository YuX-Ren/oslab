#ifndef __KMALLOC_H__
#define __KMALLOC_H__

#include "mem.h"

unsigned long kalloc(unsigned long size);
unsigned long kfree(unsigned long start);
unsigned long kstackalloc();
unsigned long kstackfree(unsigned long stack);
#endif