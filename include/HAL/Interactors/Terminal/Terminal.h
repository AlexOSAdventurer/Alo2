#pragma once 

#include <stdint-gcc.h>  
#include <stddef.h> 
#include <HAL/Drivers/TextModeVGA/TextModeVGA.h> 
#include <Utility/Utility.h> 

typedef VGA_color terminal_color; 

static const size_t terminal_height = 24; 
static const size_t terminal_width = 80; 

static size_t terminal_currentx = 0; 
static size_t terminal_currenty = 0; 


static terminal_color terminal_currentforeground = GREEN;  

static terminal_color terminal_currentbackground = BLACK; 

void terminal_init(void); 

void terminal_putchar(char character, terminal_color background, terminal_color foreground); 


void terminal_putstring(const char* str); 

void terminal_movecursor(int x, int y); 