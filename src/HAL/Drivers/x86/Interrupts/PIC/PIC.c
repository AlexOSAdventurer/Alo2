#include <HAL/Drivers/x86/Interrupts/PIC/PIC.h> 

uint16_t PIC_get_irq_register(int ocw3) { 
	outportb(PIC1_COMMANDPORT, ocw3); 
	outportb(PIC2_COMMANDPORT, ocw3); 
	return (inportb(PIC2_COMMANDPORT) << 8) | inportb(PIC1_COMMANDPORT); 
}; 

uint16_t PIC_get_irr(void) { 
	return PIC_get_irq_register(PIC_READ_IRR); 
}; 

uint16_t PIC_get_isr(void) { 
	return PIC_get_irq_register(PIC_READ_ISR); 
}; 

void PIC_SetMask(int irqnumber) { 
	uint16_t theport; 
	uint8_t value; 
	
	if (irqnumber < 8) { 
		theport = PIC1_DATAPORT; 
	} 
	else { 
		theport = PIC2_DATAPORT; 
		irqnumber = irqnumber - 8; 
	}; 
	value = inportb(theport) | (1 << irqnumber); 
	outportb(theport, value); 
}; 

void PIC_ClearMask(int irqnumber) { 
	uint16_t theport; 
	uint8_t value; 
	
	if (irqnumber < 8) { 
		theport = PIC1_DATAPORT; 
	} 
	else { 
		theport = PIC2_DATAPORT; 
		irqnumber = irqnumber - 8; 
	}; 
	value = inportb(theport) & ~(1 << irqnumber); 
	outportb(theport, value); 
}; 

void PIC_remap(int firstoffset, int secondoffset) { 
	uint8_t mask1, mask2; 
	
	mask1 = inportb(PIC1_DATAPORT); 
	mask2 = inportb(PIC2_DATAPORT); 
	
	outportb(PIC1_COMMANDPORT,  0x11); 
	io_wait(); 
	outportb(PIC2_COMMANDPORT, 0x11); 
	io_wait(); 
	outportb(PIC1_DATAPORT, firstoffset); 
	io_wait(); 
	outportb(PIC2_DATAPORT, secondoffset); 
	io_wait(); 
	outportb(PIC1_DATAPORT, 4); 
	io_wait(); 
	outportb(PIC2_DATAPORT, 2); 
	io_wait(); 
	
	outportb(PIC1_DATAPORT, 0x01); 
	io_wait(); 
	outportb(PIC2_DATAPORT, 0x01); 
	io_wait(); 
	
	outportb(PIC1_DATAPORT, mask1); 
	outportb(PIC2_DATAPORT, mask2); 
}; 

void PIC_SendEOI(int irqnumber) { 
	if (irqnumber >= 8) { 
		outportb(PIC2_COMMANDPORT, PIC_EOI); 
	}; 
	outportb(PIC1_COMMANDPORT, PIC_EOI); 
}; 

void PIC_Disable(void) { 
	outportb(PIC1_COMMANDPORT, PIC_DISABLECODE); 
	outportb(PIC2_COMMANDPORT, PIC_DISABLECODE); 
	io_wait(); 
}; 


void PIC_init(void) { 
	PIC_remap(32, 47); 
}; 

