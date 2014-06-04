#include <HAL/Drivers/x86/PIT/PIT.h> 
#include <stdbool.h> 

typedef PITCallback TimerCallback; 

static struct Timer_struct { 
	TimerCallback func; 
	int tick; 
	int limit; 
	struct Timer_struct* next; 
	struct Timer_struct* behind; 
}; 

typedef struct Timer_struct Timer; 

void Timer_Register_Timer(Timer* thetimer); 

void Timer_DeRegister_Timer(Timer* ourtimer); 

void Timer_init(void); 

