#include <Memory/kmalloc_nfree.h>
#include <HAL/Interactors/Terminal/Terminal.h>
#include <Utility/Utility.h>
#include <stdint-gcc.h>

#define max_memory 10485760

uint32_t current_addr;


void kmalloc_nfree_init(void) { 
	current_addr = (uint32_t)_kmalloc_nfree_addr;
	_kmalloc_max_addr = ((current_addr + max_memory) & 0xFFFFF000) + 0x1000;
	terminal_printf("Starting kmalloc_nfree addr: %h, %h.", current_addr, _kmalloc_nfree_addr);
};

uint32_t kmalloc_nfree_usage(void) { 
	return current_addr - (uint32_t)(_kmalloc_nfree_addr);
};


void* kmalloc_nfree(size_t size, int aligned) { 
	void* ptr;
	if (aligned) { 
		current_addr = current_addr & 0xFFFFF000;
		current_addr = current_addr + 0x1000;
	};
	ptr = (void*)current_addr;
	current_addr = current_addr + size;
	if (current_addr > _kmalloc_max_addr) { 
		panic("kmalloc_nfree memory range exceeded!");
	};
	return ptr; 
}; 





