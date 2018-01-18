#include <system-lib/system_lib.h>

static size_t m_api_number = 48;

void system_lib_handler(interrupt_stackstate* state) { 
	uint32_t eax = state->eax;
	if (eax < LIB_H_MAX) { 
		if (system_lib_handlers[eax] != NULL) { 
			state->eax = 0;
			system_lib_handlers[eax](state);
			return;
		};
	}
	state->eax = 1;
};

void system_lib_printf(interrupt_stackstate* state) { 
	terminal_printf((const char*)state->edx);
};

void system_lib_init(void) { 
	memset(system_lib_handlers, 0, sizeof(interrupthandlerfunc) * LIB_H_MAX);
	InterruptHandlers[m_api_number] = system_lib_handler;
	system_lib_handlers[1] = system_lib_printf;
};
