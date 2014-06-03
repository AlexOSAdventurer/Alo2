#include <HAL/Drivers/x86/Interrupts/Interrupts.h> 

void interrupts_init(void) { 	
	PIC_init(); 
	IDT_init(); 
	__asm__  __volatile__("sti"); 
}; 
