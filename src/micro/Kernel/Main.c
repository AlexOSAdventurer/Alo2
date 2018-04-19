#include <HAL/hal.h> 
#include <GRUB/multiboot.h> 
#include <Utility/Utility.h> 
#include <Process/process.h>
#include <gcc-lib-funcs/gcc-lib-funcs.h>
#include <system-lib/system_lib.h>
 

void Alo_Main(multiboot_data *multibootdata) { 
	HAL_init(multibootdata);  
	terminal_putstring("Hello to Alo 2!\n"); 
	terminal_printf("Number of modules: %d.", (int) multibootdata->numberofmodules);	
	if (multibootdata->numberofmodules > 0) {
		const char** mod = (const char**) multibootdata->addressoffirstmodule;
		terminal_printf("Address: %h.", (int) mod);
		terminal_putstring("Contents:\n");
		terminal_putstring(*mod + 0x200);
		terminal_putstring("\n");
		terminal_putstring("Booting initrd process....\n");
		spawn_process((void*)(*mod + 0x200), 512);
	}
	int* array = kmalloc(sizeof(int) * 11);
	char* str = kmalloc(sizeof(char) * 16);
	page_dir_t* d = kmalloc_a(sizeof(page_dir_t) * 1024, 4096, NULL);
	page_dir_t* d2 = kmalloc_a(sizeof(page_dir_t) * 1024, 4096, NULL);
	page_dir_t* d3 = kmalloc_a(sizeof(page_dir_t) * 1024, 4096, NULL);
	uint32_t p1 = paging_get_phys((uint32_t)array), p2 = paging_get_phys((uint32_t)str), p3 = paging_get_phys((uint32_t)d), p4 = paging_get_phys((uint32_t)d2), p5 = paging_get_phys((uint32_t)d3);
	uint32_t v1 = paging_get_virt(p1), v2 = paging_get_virt(p2), v3 = paging_get_virt(p3), v4 = paging_get_virt(p4), v5 = paging_get_virt(p5);
	memcpy(str, "This is a test.\n", 17);
	terminal_printf("Addresses: %h, %h, %h, %h, %h. Sizes: %d, %d, %d, %d, %d.", (int)array, (int)str, (int)d, (int)d2, (int)d3,  kmalloc_get_size(array), kmalloc_get_size(str), kmalloc_get_size(d), kmalloc_get_size(d2), kmalloc_get_size(d3));
	terminal_printf("Phys: %h, %h, %h, %h, %h. ", p1, p2, p3, p4, p5);
	terminal_printf("Convert back: %h, %h, %h, %h, %h.", v1, v2, v3, v4, v5);
	terminal_printf("Convert: %h to %h", 0x1000, paging_get_phys(0x1000));
	terminal_putstring(str);
	terminal_putstring("Test complete.\n");
	kfree(array);
	kfree(str); 
	kfree(d);
	/*while (1) { 
		terminal_putstring("BEFORE YIELD!\n");
		yield();
		terminal_putstring("AFTER YIELD!\n");
	};*/
	//kfree((void*)Alo_Main);*/
}; 
