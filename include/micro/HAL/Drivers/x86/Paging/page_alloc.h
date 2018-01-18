#ifndef PAGE_ALLOC_H
#define PAGE_ALLOC_H

#include <stddef.h>

typedef struct page_alloc { 
	uint32_t addr;
	uint32_t p;
	struct page_alloc* prev;
	struct page_alloc* next;
} page_alloc_t;

int alloc_page_p(size_t p_n, page_dir_t* dir);
int alloc_page(uint32_t addr, page_dir_t* dir);
void free_page(uint32_t addr, page_dir_t* dir, uint32_t p);
void page_alloc_init(uint32_t max_page, uint32_t max_kern_page);

#endif