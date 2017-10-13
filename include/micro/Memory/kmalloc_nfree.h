#ifndef KMALLOC_NFREE
#define KMALLOC_NFREE

#include <stddef.h>


void kmalloc_nfree_init(void);

void* kmalloc_nfree(size_t size, int aligned);




#endif