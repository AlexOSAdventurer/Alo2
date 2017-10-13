#include <HAL/Drivers/x86/Paging/paging.h>
#include <Memory/kmalloc_nfree.h>


page_dir_t kernel_dir[1024] __attribute__((aligned(4096)));


static int ceil_i(int n, int d) { 
	int res = 0;
	if (n % d) { 
		res++;
	}
	res = res + (n / d);
	return res;
}

page_table_t* paging_create_kernel_table(int i, int n) {
	page_table_t* table = (page_table_t*)kmalloc_nfree(1024 * sizeof(page_table_t), 1);
	for (int z = 0; z < n; z++) { 
		table[z].present = 1;
		table[z].rw = 1;
		table[z].us = 0;
		table[z].wt = 0;
		table[z].cache = 0;
		table[z].accessed = 0; 
		table[z].dirty = 0;
		table[z].zero = 0;
		table[z].global = 0; 
		table[z].avail = 0;
		table[z].addr = (4096 * ((i * 1024) + z)) >> 12;
	}
	
	for (int z = n; z < 1024; z++) {
		table[z].present = 0;
	};
	return table;
}

static void paging_create_kernel_dir(uint32_t max_addr) {
	int dir_entries = ceil_i((int)max_addr, 4194304);
	
	for (int i = 0; i < dir_entries; i++) { 
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
		kernel_dir[i].addr = ((uint32_t)paging_create_kernel_table(i, max)) >> 12;
	};
	for (int i = dir_entries; i < 1024; i++) { 
		kernel_dir[i].present = 0;
	};
}

	

void paging_load_kernel_dir(uint32_t max_addr) { 
	paging_create_kernel_dir(max_addr);
	paging_load_dir(kernel_dir);
}


void paging_init(uint32_t max_addr) { 
	paging_load_kernel_dir(max_addr);
	paging_enable();
}