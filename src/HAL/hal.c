#include <HAL/hal.h> 

void HAL_init(multiboot_data *multibootinfo) { 
	UNUSED(multibootinfo); 
	GDT_init(); 
	interrupts_init();  
	terminal_init(); 
	Timer_init(); 
}; 
