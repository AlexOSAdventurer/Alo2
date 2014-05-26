#pragma once 

#include <HAL/Interactors/Terminal/Terminal.h> 
#include <stdint-gcc.h> 

#define ASSERT_FORMATSTR "Assertion failed! \n File: %s. \n Line: %s. " 

#define ASSERT(condition) do { if (!(condition)) { printf(ASSERT_FORMATSTR, RED, BLACK, __FILE__, _(__LINE__)); panic("Fatal error! "); }; }  

#define UNUSED(var) (void)(var) 

void panic(const char* msg); 

void outportb(uint16_t port, uint8_t thevalue); 

uint8_t inportb(uint16_t port);    

void io_wait(void); 



