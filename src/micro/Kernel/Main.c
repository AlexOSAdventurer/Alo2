#include <HAL/hal.h> 
#include <GRUB/multiboot.h> 
#include <Utility/Utility.h> 
 

void Alo_Main(multiboot_data *multibootdata) { 
	HAL_init(multibootdata);  
	terminal_putstring("Hello to Alo 2!\n"); 
	terminal_printf("Number of modules: %d.", (int) multibootdata->numberofmodules);	
	if (multibootdata->numberofmodules > 0) { 
		const char** mod = (const char**) multibootdata->addressoffirstmodule;
		terminal_printf("Address: %h.", (int) multibootdata->addressoffirstmodule);
		terminal_putstring("Contents:\n");
		terminal_putstring(*mod + 0x200);
	}
}; 
