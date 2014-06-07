#include <HAL/Drivers/x86/Interrupts/Interrupts.h> 



void interrupts_disable(void) { 
	__asm__  __volatile__("cli"); 
}; 

void interrupts_enable(void) { 
	__asm__  __volatile__("sti");  
}; 


void interrupts_init(void) { 	
	PIC_init(); 
	IDT_init(); 
	interrupts_enable(); 
}; 
