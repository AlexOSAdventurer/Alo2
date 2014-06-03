#include <HAL/hal.h> 

void HAL_init(multiboot_info_t *multibootinfo) { 
	UNUSED(multibootinfo); 
	GDT_init(); 
	interrupts_init();  
	terminal_init(); 
}; 
