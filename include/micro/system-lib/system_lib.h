#ifndef LIB_H 
#define LIB_H

#include <HAL/Drivers/x86/Interrupts/Interrupts.h>
#include <gcc-lib-funcs/gcc-lib-funcs.h>

#define LIB_H_MAX 1024

interrupthandlerfunc system_lib_handlers[LIB_H_MAX];


void system_lib_init(void);

void yield(void);

#endif