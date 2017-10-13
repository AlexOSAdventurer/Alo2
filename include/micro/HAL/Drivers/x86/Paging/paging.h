#ifndef PAGING_H
#define PAGING_H

#include <stdint-gcc.h>

typedef struct {
	uint32_t present	: 1;
	uint32_t rw			: 1;
	uint32_t us			: 1;
	uint32_t wt			: 1;
	uint32_t cache		: 1;
	uint32_t accessed	: 1;
	uint32_t zero		: 1;
	uint32_t size		: 1;
	uint32_t ignored	: 1;
	uint32_t avail		: 3;
	uint32_t addr		: 20;
} page_dir_t __attribute__((packed));

typedef struct {
	uint32_t present	: 1;
	uint32_t rw			: 1;
	uint32_t us			: 1;
	uint32_t wt			: 1;
	uint32_t cache		: 1;
	uint32_t accessed	: 1;
	uint32_t dirty		: 1;
	uint32_t zero		: 1;
	uint32_t global		: 1;
	uint32_t avail		: 3;
	uint32_t addr		: 20;
} page_table_t __attribute__((packed));


void paging_load_dir(page_dir_t*);
void paging_load_kernel_dir(uint32_t max_addr);

void paging_enable(void);
void paging_disable(void);

void paging_init(uint32_t max_addr);



#endif