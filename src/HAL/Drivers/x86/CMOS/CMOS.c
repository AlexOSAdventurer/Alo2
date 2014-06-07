#include <HAL/Drivers/x86/CMOS/CMOS.h> 

static uint8_t NMI_Status = 1; 

void CMOS_Disable_NMI(void) {  
	NMI_Status = 1; 
	outportb(0x70, 0x80); 
	io_wait(); 
}; 

void CMOS_Enable_NMI(void) { 
	NMI_Status = 0; 
	outportb(0x70, 0); 
	io_wait(); 
}; 

uint8_t CMOS_GetRegister(int reg) { 
	if (reg <= 8) { 
		while (((CMOS_GetRegister(10) & 0x40) >> 6)); 
	}; 
	outportb(0x70, (NMI_Status << 7) | reg); 
	io_wait(); 
	return inportb(0x71); 
}; 


