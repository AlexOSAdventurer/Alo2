#include <HAL/Drivers/x86/PIT/PIT.h> 

static int timerstate = 0; 

 void PIT_Handler(interrupt_stackstate *thestack) { 
	if (ThePITCallback) { 
		ThePITCallback(thestack); 
	}; 
}; 

int PIT_GetTimerNumber(void) { 
	return timerstate; 
}; 

void PIT_sethz(int rate) { 
	int thedivisor = 1193180/rate; 
	outportb(0x43, 0x36); 
	outportb(0x40, thedivisor & 0xFF); 
	outportb(0x40, thedivisor >> 8); 
}; 

void PIT_init(void) { 
	PIT_sethz(100); /* Timer will fire every 10 milliseconds. */ 
	InterruptHandlers[32] = PIT_Handler; 
	ThePITCallback = 0; 
}; 
