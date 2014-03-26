#include "../../../../include/Kernel/Interrupts/ISR/isr.h" 

void isr_fault_handler(fault_regs_t registers) { 
	uint32_t interruptnumber = registers.int_no; 
	if (interruptnumber > 19) { 
		interruptnumber = 19; 
	}; 
	VGA_printf("%s Exception! System Halted!", msgs[interruptnumber]); 
	__asm__("cli"); 
	__asm__("hlt"); 
}; 

void isrs_init(void) { 
	idt_set_gate(&idt[0], (uint32_t)isr0, 0x08, 0x8E); 
	idt_set_gate(&idt[1], (uint32_t)isr1, 0x08, 0x8E); 
	idt_set_gate(&idt[2], (uint32_t)isr2, 0x08, 0x8E); 
	idt_set_gate(&idt[3], (uint32_t)isr3, 0x08, 0x8E); 
	idt_set_gate(&idt[4], (uint32_t)isr4, 0x08, 0x8E); 
	idt_set_gate(&idt[5], (uint32_t)isr5, 0x08, 0x8E); 
	idt_set_gate(&idt[6], (uint32_t)isr6, 0x08, 0x8E); 
	idt_set_gate(&idt[7], (uint32_t)isr7, 0x08, 0x8E); 
	idt_set_gate(&idt[8], (uint32_t)isr8, 0x08, 0x8E); 
	idt_set_gate(&idt[9], (uint32_t)isr9, 0x08, 0x8E); 
	idt_set_gate(&idt[10], (uint32_t)isr10, 0x08, 0x8E); 
	idt_set_gate(&idt[11], (uint32_t)isr11, 0x08, 0x8E); 
	idt_set_gate(&idt[12], (uint32_t)isr12, 0x08, 0x8E); 
	idt_set_gate(&idt[13], (uint32_t)isr13, 0x08, 0x8E); 
	idt_set_gate(&idt[14], (uint32_t)isr14, 0x08, 0x8E); 
	idt_set_gate(&idt[15], (uint32_t)isr15, 0x08, 0x8E); 
	idt_set_gate(&idt[16], (uint32_t)isr16, 0x08, 0x8E); 
	idt_set_gate(&idt[17], (uint32_t)isr17, 0x08, 0x8E); 
	idt_set_gate(&idt[18], (uint32_t)isr18, 0x08, 0x8E); 
	idt_set_gate(&idt[19], (uint32_t)isr19, 0x08, 0x8E); 
	idt_set_gate(&idt[20], (uint32_t)isr20, 0x08, 0x8E); 
	idt_set_gate(&idt[21], (uint32_t)isr21, 0x08, 0x8E); 
	idt_set_gate(&idt[22], (uint32_t)isr22, 0x08, 0x8E); 
	idt_set_gate(&idt[23], (uint32_t)isr23, 0x08, 0x8E); 
	idt_set_gate(&idt[24], (uint32_t)isr24, 0x08, 0x8E); 
	idt_set_gate(&idt[25], (uint32_t)isr25, 0x08, 0x8E); 
	idt_set_gate(&idt[26], (uint32_t)isr26, 0x08, 0x8E); 
	idt_set_gate(&idt[27], (uint32_t)isr27, 0x08, 0x8E); 
	idt_set_gate(&idt[28], (uint32_t)isr28, 0x08, 0x8E); 
	idt_set_gate(&idt[29], (uint32_t)isr29, 0x08, 0x8E); 
	idt_set_gate(&idt[30], (uint32_t)isr30, 0x08, 0x8E); 
	idt_set_gate(&idt[31], (uint32_t)isr31, 0x08, 0x8E); 
}; 


