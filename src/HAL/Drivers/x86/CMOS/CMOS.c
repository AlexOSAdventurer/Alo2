#include <HAL/Drivers/x86/CMOS/CMOS.h> 

static uint8_t NMI_Status = 1; 

void CMOS_Disable_NMI(void) {  
	interrupts_disable(); 
	NMI_Status = 1; 
	outportb(0x70, 0x80); 
	io_wait(); 
	interrupts_enable(); 
}; 

void CMOS_Enable_NMI(void) { 
	interrupts_disable(); 
	NMI_Status = 0; 
	outportb(0x70, 0); 
	io_wait(); 
	interrupts_enable(); 
}; 

uint8_t CMOS_GetRegister(int reg) { 
	interrupts_disable(); 
	uint8_t res; 
	if (reg <= 8) { 
		while (((CMOS_GetRegister(10) & 0x40) >> 6)); 
	}; 
	outportb(0x70, (NMI_Status << 7) | reg); 
	io_wait(); 
	res = inportb(0x71); 
	interrupts_enable(); 
	return res; 
}; 


void CMOS_WriteToRegister(int thereg, uint8_t val) 
	interrupts_disable(); 
	outportb(0x70, (NMI_Status << 7) | thereg); 
	io_wait(); 
	outportb(0x71, val); 
	io_wait(); 
	interrupts_enable(); 
}; 

