#ifndef KMALLOC_NFREE
#define KMALLOC_NFREE

#include <stdint-gcc.h>
#include <stddef.h>

extern char _kmalloc_nfree_addr[];
uint32_t _kmalloc_max_addr;

void kmalloc_nfree_init(void);

uint32_t kmalloc_nfree_usage(void);

void* kmalloc_nfree(size_t size, int aligned);




#endif