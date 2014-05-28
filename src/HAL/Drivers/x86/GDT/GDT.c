#include <HAL/Drivers/x86/GDT/GDT.h> 

void SetGDTEntry(int entrynumber, uint32_t base, uint32_t limit, uint8_t access, uint8_t granularity) { 
	thegdt[entrynumber].access = access; 
	
	thegdt[entrynumber].base_low = (base & 0xFFFF); 
	thegdt[entrynumber].limit_low =  (limit & 0xFFFF); 
	thegdt[entrynumber].granularity = ((limit >> 16) & 0x0F) | (granularity & 0xF0); 
	
	thegdt[entrynumber].base_middle = ((base >> 16) & 0xFF); 
	thegdt[entrynumber].base_high = (base >> 24) & 0xFF; 
	
}; 

void LoadThe_GDT(uint32_t codeoffset, uint32_t dataoffset) { 
	load_gdt(gdtpointer, dataoffset, codeoffset); 
};  

void GDT_init(void) { 
	gdtpointer.size = 23; 
	gdtpointer.address = &thegdt; 
	SetGDTEntry(1, 0, 0xFFFFFFFF, 0x9A, 0xCF); 
	SetGDTEntry(0, 0, 0, 0, 0); 
	
	SetGDTEntry(2, 0, 0xFFFFFFFF, 0x92, 0xCF);  
	
	LoadThe_GDT(0x08, 0x10); 
}; 

