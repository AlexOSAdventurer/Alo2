#include <Memory/kmalloc_nfree.h>
#include <HAL/Interactors/Terminal/Terminal.h>
#include <stdint-gcc.h>

extern char _kmalloc_nfree_addr[];

uint32_t current_addr;


void kmalloc_nfree_init(void) { 
	current_addr = (uint32_t)_kmalloc_nfree_addr;
	terminal_printf("Starting kmalloc_nfree addr: %h, %h.", current_addr, _kmalloc_nfree_addr);
};



void* kmalloc_nfree(size_t size, int aligned) { 
	void* ptr;
	if (aligned) { 
		current_addr = current_addr & 0xFFFFF000;
		current_addr = current_addr + 0x1000;
	};
	ptr = (void*)current_addr;
	current_addr = current_addr + size;
	return ptr; 
};