#include <HAL/hal.h> 
#include <stdint-gcc.h>
#include <Utility/Utility.h>

void HAL_init(multiboot_data *multibootinfo) { 
	uint32_t max_addr = 1024;
	GDT_init(); 
	interrupts_init();  
	terminal_init();
	kmalloc_nfree_init();
	Timer_init(); 
	if (multibootinfo->flags & 1) { 
		max_addr = max_addr + multibootinfo->highermemory;
		max_addr = max_addr * 1024;
		terminal_printf("Mem_lower: %d. Mem_upper: %d. Max_addr: %h.", (int)multibootinfo->lowermemory, (int)multibootinfo->highermemory, (int)max_addr);
	}
	else { 
		panic("Multiboot memory not available!");
	};
	paging_init(max_addr);
	kmalloc_init();
	system_lib_init();
	task_init();
}; 
