#pragma once 
#include <stdint-gcc.h> 


typedef struct __attribute__((packed))  { 
	uint16_t limit_low; 
	uint16_t base_low; 
	uint8_t base_middle; 
	uint8_t access; 
	uint8_t granularity; 
	uint8_t base_high; 
} gdt_entry; 

typedef struct __attribute__((packed)) { 
	uint16_t size; 
	uint32_t address; 
} gdt_pointer; 


static gdt_entry thegdt[3]; 

static gdt_pointer gdtpointer; 

void load_gdt(gdt_pointer ptr, uint32_t dataoffset, uint32_t codeoffset); 

void SetGDTEntry(int entrynumber, uint32_t base, uint32_t limit, uint8_t access, uint8_t granularity); 

void GDT_init(void); 


