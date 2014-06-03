#pragma once 

#include <stdint-gcc.h>  
#include <stddef.h> 
#include <HAL/Drivers/TextModeVGA/TextModeVGA.h>
#include <Utility/Utility.h>
#include <stdarg.h> 

typedef VGA_color terminal_color; 


void terminal_init(void); 

void terminal_putchar(char character, terminal_color background, terminal_color foreground); 


void terminal_putstring(const char* str); 

void terminal_movecursor(int x, int y); 

void terminal_printf(const char *str, ...); 