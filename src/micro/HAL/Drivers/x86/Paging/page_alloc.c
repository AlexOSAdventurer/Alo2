#include <Memory/kmalloc_nfree.h>
#include <HAL/Interactors/Terminal/Terminal.h>
#include <stdint-gcc.h>
#include <HAL/Drivers/x86/Paging/paging.h>
#include <stddef.h>

#define TABLE_INDEX(i) (i / 32)
#define TABLE_OFFSET(i) (i % 32) 

#define MAX_PAGE_AM 1048576
#define MAX_ADDRESS_AM MAX_PAGE_AM / 32


uint32_t* page_alloc_d;
int page_alloc_size;




static void set_page_prim(int i, int o) { 
	page_alloc_d[i] |= (1 << o);
};


int test_page_prim(int i, int o) { 
	return ((page_alloc_d[i] & (1 << o)) > 0);
};

static void clear_page_prim(int i, int o) {
	page_alloc_d[i] &= ~(1 << o);
};

static void set_page(uint32_t p) { 
	set_page_prim(TABLE_INDEX(p), TABLE_OFFSET(p));
};

static int test_page(uint32_t p) { 
	return test_page_prim(TABLE_INDEX(p), TABLE_OFFSET(p));
};

static void clear_page(uint32_t p) { 
	clear_page_prim(TABLE_INDEX(p), TABLE_OFFSET(p));
};

//static void get_page(uint32_t addr) { 
	
int first_frame() { 
	for (int i = 0; i < MAX_ADDRESS_AM; i++) { 
		if (page_alloc_d[i] != 0xFFFFFFFF) {
			for (int j = 0; j < 32; j++) { 
				if (!test_page_prim(i, j)) { 
					return (i * 32) + j;
				};
			}
		}	
	};	
	return -1; 
};


int _alloc_page() { 
	int res = first_frame();
	if (res != -1) { 
		set_page(res);
	};
	return res;
};

int alloc_page(uint32_t addr, page_dir_t* dir) { 
	int p = _alloc_page();
	if (p != -1) { 
		size_t p_n = addr / 4096; 
		size_t dir_n = p_n / 1024; 
		p_n = p_n % 1024;
		page_table_t* p_list = (page_table_t*)(dir[dir_n].addr << 12);
		p_list[p_n].present = 1;
		p_list[p_n].addr = (4096 * (uint32_t)p) >> 12;
		p_list[p_n].rw = 1;
	}
	return p;
}


void _free_page(uint32_t p) {
	clear_page(p);
};	

void free_page(uint32_t addr, page_dir_t* dir, uint32_t p) { 
	_free_page(p);
	size_t p_n = addr / 4096; 
	size_t dir_n = p_n / 1024; 
	p_n = p_n % 1024;
	dir_n--;
	page_table_t* p_list = (page_table_t*)(dir[dir_n].addr << 12);
	p_list[p_n].present = 0;
	p_list[p_n].addr = 0;
};


void page_alloc_init(uint32_t max_page, uint32_t max_kern_page) { 
	terminal_printf("Max page: %h.", (int)max_page);
	terminal_printf("Kernel dir: %h.", (uint32_t) kernel_dir);
	page_alloc_d = (uint32_t*)kmalloc_nfree(MAX_ADDRESS_AM, 0);
	for (int i = 0; i < (max_kern_page / 32); i++) { 
		page_alloc_d[i] = 0xFFFFFFFF;
	};
	
	for (int i = (max_page / 32) - 1; i < (MAX_ADDRESS_AM  - 1); i++) { 
		page_alloc_d[i] = 0xFFFFFFFF;
	};
};