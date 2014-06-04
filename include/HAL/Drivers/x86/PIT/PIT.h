#pragma once 

#include <HAL/Drivers/x86/Interrupts/Interrupts.h> 
#include <Utility/Utility.h> 
#include <HAL/Interactors/Terminal/Terminal.h> 

typedef interrupthandlerfunc PITCallback; 

PITCallback ThePITCallback; 

int PIT_GetTimerNumber(void);  

void PIT_sethz(int rate); 
	
void PIT_init(void); 


