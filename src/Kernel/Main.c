#include <HAL/hal.h> 
#include <GRUB/multiboot.h> 


void Alo_Main(multiboot_info_t *multibootdata) { 
	HAL_init(multibootdata); 
	terminal_putstring("Hello to Alo 2!\n"); 
	terminal_putstring(" Just testing newlines...."); 
}; 
