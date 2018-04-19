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
} __attribute__((packed)) page_dir_t;

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
} __attribute__((packed)) page_table_t;

#include <HAL/Drivers/x86/Paging/page_alloc.h>

#define PAGING_PAGE_SIZE 0x1000
#define PAGING_PAGE_TABLE_LIST_SIZE 0x400
#define PAGING_PAGE_TABLE_LIST_ADDR_SIZE (PAGING_PAGE_SIZE * PAGING_PAGE_TABLE_LIST_SIZE)

#define PAGING_PAGE_DIRECTORY_SIZE PAGING_PAGE_TABLE_LIST_ADDR_SIZE
#define PAGING_PAGE_DIRECTORY_LIST_SIZE 0x400
#define PAGING_PAGE_DIRECTORY_LIST_ADDR_SIZE (PAGING_PAGE_DIRECTORY_SIZE * PAGING_PAGE_DIRECTORY_LIST_SIZE)

#define PAGING_MEM_MAX 0x100000000


page_dir_t* kernel_dir;
page_dir_t* paging_cur_dir;

page_table_t* paging_create_table(uint32_t* phys);
page_dir_t* paging_create_dir(uint32_t* phys);

void _paging_load_dir(uint32_t);
void paging_load_dir(page_dir_t* d);
page_dir_t* paging_get_dir(void);
void paging_load_kernel_dir(uint32_t max_addr);

uint32_t paging_get_phys(uint32_t addr);
uint32_t paging_get_virt(uint32_t addr);

void paging_enable(void);
void paging_disable(void);

void paging_init(uint32_t max_addr);



#endif
