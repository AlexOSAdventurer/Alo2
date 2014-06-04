#include <HAL/hal.h> 
#include <GRUB/multiboot.h> 
#include <Utility/Utility.h> 

volatile Timer testtimer; 
volatile Timer secondtimer; 

void TheResponse(interrupt_stackstate *lstack) { 
	terminal_printf("About two seconds has passed."); 
}; 

void OneSecondHandler(interrupt_stackstate *lstack) { 
	terminal_printf("About one second has passed."); 
}; 

void Alo_Main(multiboot_info_t *multibootdata) { 
	HAL_init(multibootdata); 
	terminal_putstring("Hello to Alo 2!\n"); 
	terminal_putstring(" Just testing newlines....\n"); 
	terminal_printf("-13 when put through itoa is: %d.", -13); 
	terminal_printf("My name is %s.", "Alex"); 
	testtimer.limit = 200; 
	testtimer.tick = 0; 
	testtimer.func = TheResponse; 
	secondtimer.limit = 100; 
	secondtimer.tick = 0; 
	secondtimer.func = OneSecondHandler; 
	Timer_Register_Timer(&testtimer); 
	Timer_Register_Timer(&secondtimer); 
	/* int test = 8/(6 - (3 * 2)); */ 
}; 
