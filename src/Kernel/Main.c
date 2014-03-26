#include "../../include/Kernel/BasicVGA/BasicVGA.h" 
#include "../../include/GRUB/multiboot.h" 
#include "../../include/Kernel/GDT/GDT.h" 
#include "../../include/Kernel/Interrupts/IDT/idt.h" 

int DivideByZero(void) { 
	return 4/(4 - 4); 
}; 

void Alo_Main(multiboot_info_t* multibootdata, uint32_t magic) { 
	VGA_init(); 
	VGA_printf("Hello OS world!\nTesting newlines! %s", "\nTesting String stuff!"); 
	gdt_init(); 
	idt_init(); 
	isrs_init(); 
}; 
