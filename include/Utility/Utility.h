#pragma once 

#include <HAL/Interactors/Terminal/Terminal.h>
#include <stdint-gcc.h> 

#define ASSERT_FORMATSTR "Assertion failed! \n File: %s. \n Line: %d. " 

#define ASSERT(condition) do { if (!(condition)) { terminal_printf(ASSERT_FORMATSTR, __FILE__, __LINE__); panic("Fatal error! "); }; } while(0)  

#define UNUSED(var) (void)(var) 

void panic(const char* msg); 

void outportb(uint16_t port, uint8_t thevalue); 

uint8_t inportb(uint16_t port);    

void io_wait(void); 


void itoa(int num, char *thespace, int base); 

