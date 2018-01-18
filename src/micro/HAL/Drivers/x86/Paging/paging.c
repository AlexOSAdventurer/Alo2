#include <HAL/Drivers/x86/Paging/paging.h>
#include <Memory/kmalloc_nfree.h>
#include <Memory/kmalloc.h>
#include <gcc-lib-funcs/gcc-lib-funcs.h>


static int ceil_i(int n, int d) { 
	int res = 0;
	if (n % d) { 
		res++;
	}
	res = res + (n / d);
	return res;
}


page_table_t* paging_create_table_p(void) { 
	page_table_t* table = (page_table_t*)kmalloc_nfree(1024 * sizeof(page_table_t), 1);
	return memset(table, 0, 1024 * sizeof(page_table_t));
};

page_dir_t* paging_create_dir_p(void) { 
	page_dir_t* dir = kmalloc_nfree(1024 * sizeof(page_dir_t), 1);
	return memset(dir, 0, 1024 * sizeof(page_dir_t));
};

page_table_t* paging_create_table(void) { 
	page_table_t* table = (page_table_t*)kmalloc_a(1024 * sizeof(page_table_t), 4096, NULL);
	return memset(table, 0, 1024 * sizeof(page_table_t));
};

page_dir_t* paging_create_dir(void) { 
	page_dir_t* dir = kmalloc_a(1024 * sizeof(page_dir_t), 4096, NULL);
	return memset(dir, 0, 1024 * sizeof(page_dir_t));
};



page_table_t* paging_create_kernel_table(int i, int n, int dir_entries) {
	page_table_t* table = paging_create_table_p();
	for (int z = 0; z < n; z++) { 
		if (i < dir_entries) { 
			table[z].present = 1;
			table[z].addr = (4096 * ((i * 1024) + z)) >> 12;
		};
		table[z].rw = 1;
		table[z].us = 0;
		table[z].wt = 0;
		table[z].cache = 0;
		table[z].accessed = 0; 
		table[z].dirty = 0;
		table[z].zero = 0;
		table[z].global = 0; 
		table[z].avail = 0;
	}
	
	for (int z = n; z < 1024; z++) {
		table[z].present = 0;
	};
	return table;
}

static void paging_create_kernel_dir(uint32_t max_addr) {
	kernel_dir = paging_create_dir_p();
	int dir_entries = ceil_i((int)max_addr, 4194304);
	
	for (int i = 0; i < 1024; i++) { 
		int max = 1024; 
		if (i == (dir_entries - 1)) { 
			max = ceil_i(max_addr % 4194304, 4096);
		};
		kernel_dir[i].present = 1;
		kernel_dir[i].rw = 1;
		kernel_dir[i].us = 0; 
		kernel_dir[i].wt = 0;
		kernel_dir[i].cache = 0;
		kernel_dir[i].accessed = 0;
		kernel_dir[i].zero = 0;
		kernel_dir[i].size = 0;
		kernel_dir[i].addr = ((uint32_t)paging_create_kernel_table(i, max, dir_entries)) >> 12;
	};
}


uint32_t paging_get_phys(uint32_t addr) { 
	size_t pd = addr / 0x400000; 
	size_t pa = addr % 0x1000;
	size_t pe = ((addr - pa) % 0x400000) / 0x1000;
	page_table_t* ptl = (page_table_t*)(paging_cur_dir[pd].addr << 12);
	page_table_t  pte = ptl[pe];
	uint32_t res = (pte.addr << 12) + pa;
	return res;
};


//Warning: this is really expensive. Try not to use it unless you have to. Seriously.
//If it fails, it returns a number smaller than 0x1000 that is exactly (addr % 0x1000) + 1. 
//Should be good enough, I guess.
uint32_t paging_get_virt(uint32_t addr) {
	uint32_t pa = addr % 0x1000;
	uint32_t tf = (addr - pa) >> 12;
	for (size_t i = 0; i < 1024; i++) { 
		for (size_t j = 0; j < 1024; j++) { 
			page_table_t* ptl = (page_table_t*)(paging_cur_dir[i].addr << 12);
			page_table_t  pte = ptl[j];
			if (pte.addr == tf) { 
				uint32_t res = (i * 0x400000) + (j * 0x1000) + pa;
				return res;
			};
		};
	};
	return pa + 1; 
};


//Warning: this could break if we start using page directory tables that differ
//from one another under the 2 GB mark. Since we aren't, it works. 
void paging_load_dir(page_dir_t* d) { 
	paging_cur_dir = d;
	_paging_load_dir(paging_get_phys((uint32_t)d));
};

void paging_load_kernel_dir(uint32_t max_addr) { 
	paging_create_kernel_dir(max_addr);
	paging_load_dir(kernel_dir);
}


void paging_init(uint32_t max_addr) { 
	paging_load_kernel_dir(_kmalloc_max_addr);
	paging_enable();
	page_alloc_init(max_addr / 4096, (uint32_t)(ceil_i(ceil_i(_kmalloc_max_addr, 4096), 32) * 32));
}