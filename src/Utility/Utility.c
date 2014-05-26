#include <Utility/Utility.h> 


void panic(const char* msg) { 
	UNUSED(msg); 
	/*printf("KERNEL PANIC: %s.", msg); */ 
	__asm__  __volatile__("cli"); /* Disable interrupts */ 
	for (;;)    ;  
}; 
