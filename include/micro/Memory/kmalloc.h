#ifndef KMALLOC_H
#define KMALLOC_H

#include <stdint-gcc.h>
#include <stddef.h>

#define KMALLOC_MIN_HEAP  4194304
#define KMALLOC_MAX_HEAP  41943040  
#define KMALLOC_MIN_EXP   16384
#define KMALLOC_MAX_DIFF 512
#define KMALLOC_MIN_BLOCK 32
#define KMALLOC_DEF_BLOCK 1024

#define KMALLOC_MAGIC_NUMBER 0xD6CCE35C487A58FE

void* kmalloc(size_t size);
void  kfree(void* ptr);
size_t kmalloc_get_size(void* ptr); 
void  kmalloc_init(void);



#endif