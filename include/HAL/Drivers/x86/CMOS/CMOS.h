#pragma once 

#include <Utility/Utility.h> 
#include <stdint-gcc.h> 
#include <HAL/Drivers/x86/Interrupts/interrupts.h> 


void CMOS_Disable_NMI(void); 

void CMOS_Enable_NMI(void); 

uint8_t CMOS_GetRegister(int reg); 

void CMOS_WriteToRegister(int thereg, uint8_t val); 

