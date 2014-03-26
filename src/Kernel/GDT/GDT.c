#include "../../../include/Kernel/GDT/GDT.h" 

void gdt_set_gate(gdt_entry_t *gdtentry, uint32_t base, uint32_t limit, uint8_t access, uint8_t granularity) { 
	gdtentry->base_low = (base & 0xFFFF); 
	gdtentry->base_middle = (base >> 16) & 0xFF; 
	gdtentry->base_high = (base >> 24) & 0xFF; 
	
	gdtentry->limit_low = (limit & 0xFFFF); 
	gdtentry->granularity = ((limit >> 16) & 0x0F); 

	gdtentry->granularity |= (granularity & 0xF0); 
	gdtentry->access = access; 
}; 

void gdt_init(void) { 
	thegdtptr.limit = (sizeof(gdt_entry_t) * 3) - 1; 
	thegdtptr.base = &thegdt; 

	gdt_set_gate(&(thegdt[0]), 0, 0, 0, 0); 
	
	gdt_set_gate(&(thegdt[1]), 0, 0xFFFFFFFF, 0x9A, 0xCF); 
	gdt_set_gate(&(thegdt[2]), 0, 0xFFFFFFFF, 0x92, 0xCF); 
	
	assign_gdt(thegdtptr); 
}; 
