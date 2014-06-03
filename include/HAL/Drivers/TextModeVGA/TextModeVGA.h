#pragma once 

#include <stdint-gcc.h> 
#include <stddef.h> 

typedef enum { 
	BLACK, BLUE, GREEN, CYAN, RED, MAGENTA, BROWN, LIGHT_GREY, DARK_GREY, LIGHT_BLUE, LIGHT_GREEN, LIGHT_CYAN, LIGHT_RED, LIGHT_MAGENTA, LIGHT_BROWN, WHITE 
} VGA_color; 

void TextModeVGA_putentry(char c, VGA_color foreground,  VGA_color background, size_t x, size_t y); 
