#include <HAL/hal.h> 

void HAL_init(multiboot_info_t *multibootinfo) { 
	UNUSED(multibootinfo); 
	terminal_init(); 
	GDT_init(); 
}; 
