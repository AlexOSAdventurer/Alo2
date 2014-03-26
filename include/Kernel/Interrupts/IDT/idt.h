#ifndef IDT 
#define IDT 


#include <stdint-gcc.h> 
#include <stddef.h> 

typedef struct __attribute__((packed)) { 
	uint16_t base_low; 
	uint16_t sel; 
	uint8_t alwayssettozero; 
	uint8_t flags; 
	uint16_t base_high; 
} idt_entry_t; 

typedef struct __attribute__((packed)) { 
	uint16_t limit; 
	uint32_t base; 
} idt_ptr_t; 

idt_entry_t idt[256]; 
idt_ptr_t theidtptr; 

void load_idt(idt_ptr_t ptr); 
void idt_set_gate(idt_entry_t *ptr, uint32_t base, uint16_t sel, uint8_t flags); 
void idt_init(void); 

#endif
