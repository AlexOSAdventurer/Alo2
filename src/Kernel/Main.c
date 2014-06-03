#include <HAL/hal.h> 
#include <GRUB/multiboot.h> 
#include <Utility/Utility.h> 

void Alo_Main(multiboot_info_t *multibootdata) { 
	HAL_init(multibootdata); 
	terminal_putstring("Hello to Alo 2!\n"); 
	terminal_putstring(" Just testing newlines....\n"); 
	terminal_printf("-13 when put through itoa is: %d.", -13); 
	terminal_printf("My name is %s.", "Alex"); 
	/* int test = 8/(6 - (3 * 2)); */ 
}; 
