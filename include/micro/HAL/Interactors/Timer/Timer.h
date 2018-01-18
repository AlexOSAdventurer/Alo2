#ifndef TIMER_H
#define TIMER_H

#include <HAL/Drivers/x86/PIT/PIT.h> 
#include <stdbool.h> 

typedef PITCallback TimerCallback; 

struct Timer_struct { 
	TimerCallback func; 
	int tick; 
	int limit; 
	volatile struct Timer_struct* next; 
	volatile struct Timer_struct* behind; 
}; 

typedef volatile struct Timer_struct Timer; 

void Timer_Register_Timer(Timer* thetimer); 

void Timer_DeRegister_Timer(Timer* ourtimer); 

void Timer_init(void); 

#endif