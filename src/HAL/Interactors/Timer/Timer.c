#include <HAL/Interactors/Timer/Timer.h> 

static volatile Timer* LeadingTimer = 0; 

static volatile bool InOperation = false; 

static void UpdateTimers(interrupt_stackstate *nstack) { 
	if (!InOperation) {  
		Timer *currenttimer = LeadingTimer; 
		while (currenttimer) { 
			if (currenttimer->tick >= currenttimer->limit) { 
				currenttimer->func(nstack); 
				currenttimer->tick = 0; 
			}; 
			currenttimer->tick++; 
			currenttimer = currenttimer->behind; 
		}; 
	}; 
}; 	

void Timer_Register_Timer(Timer* thetimer) { 
	InOperation = true; 
	Timer* formerleading = LeadingTimer; 
	LeadingTimer = thetimer; 
	thetimer->behind = formerleading; 
	thetimer->next = 0; 
	if (formerleading) { 
		formerleading->next = thetimer; 
	}; 
	InOperation = false; 
}; 	

void Timer_DeRegister_Timer(Timer* ourtimer) { 
	InOperation = true; 
	ourtimer->behind->next = ourtimer->next; 
	ourtimer->next->behind = ourtimer->behind; 
	InOperation = false; 
}; 

void Timer_init(void) { 
	PIT_init(); 
	ThePITCallback = UpdateTimers; 
}; 