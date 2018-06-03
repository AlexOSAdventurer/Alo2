#include <GRUB/multiboot.h>
#include <HAL/hal.h>

void initrd_relocate(multiboot_data* multibootdata) { 
	multiboot_modules* mods = multibootdata->modules;
	void* initrd_old = (void*)(mods->mod_start);
	size_t initrd_size = mods->mod_end - mods->mod_start + 1;
	void* initrd_new = kmalloc_nfree(initrd_size, 0); 
	memcpy(initrd_new, initrd_old, initrd_size);
	mods->mod_start = (uint32_t)initrd_new;
	mods->mod_end = mods->mod_start + initrd_size - 1;
	terminal_printf("Old location: %h. New location: %h.", (uint32_t)initrd_old, (uint32_t)initrd_new);
} 

void initrd_load(multiboot_data* multibootdata) { 
	terminal_printf("Number of modules: %d.", (int) multibootdata->numberofmodules);	
	if (multibootdata->numberofmodules > 0) {
		const char* mod = (const char*) multibootdata->modules->mod_start;
		terminal_printf("Address: %h.", (int) mod);
		terminal_putstring("Contents:\n");
		terminal_putstring(mod + 0x200);
		terminal_putstring("\n");
		terminal_putstring("Booting initrd process....\n");
		spawn_process((void*)(mod + 0x200), 512);
	}
};
