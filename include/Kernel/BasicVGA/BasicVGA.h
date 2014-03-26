#ifndef BasicVGA 
#define BasicVGA 
#if !defined(__cplusplus) 
	#include <stdbool.h> 
#endif 

#include <stddef.h> 
#include <stdarg.h> 
#include <stdint-gcc.h> /* Originally tried using stdint.h, but some weird preprocessor macho in that header caused it to try to include the wrong header, so I just used stdint-gcc instead. */ 
#include "../Ports/Port.h" 
	

typedef enum VGA_color_val 
{ 
	COLOR_BLACK = 0,
	COLOR_BLUE = 1,
	COLOR_GREEN = 2,
	COLOR_CYAN = 3,
	COLOR_RED = 4,
	COLOR_MAGENTA = 5,
	COLOR_BROWN = 6,
	COLOR_LIGHT_GREY = 7,
	COLOR_DARK_GREY = 8,
	COLOR_LIGHT_BLUE = 9,
	COLOR_LIGHT_GREEN = 10,
	COLOR_LIGHT_CYAN = 11,
	COLOR_LIGHT_RED = 12,
	COLOR_LIGHT_MAGENTA = 13,
	COLOR_LIGHT_BROWN = 14,
	COLOR_WHITE = 15
} VGA_color_val; 

uint16_t* VGA_buffer; 
uint8_t VGA_color; 
size_t VGA_row; 
size_t VGA_column; 

static const size_t VGA_WIDTH = 80; 
static const size_t VGA_HEIGHT = 24; 


void VGA_init(); /* Initializes the VGA screen and makes it so you can safely call the screen manipulation functions; always call this before using the driver for safety's sake! */
uint8_t VGA_makecolor(VGA_color_val foreground, VGA_color_val background); /* makes a usable color value for the entries in this video mode */ 
void VGA_movecursor(size_t x, size_t y); /* Moves the cursor to the set position */ 
void VGA_setcolor(uint8_t color); /* sets it so that is the color that is used when putting characters on screen from that point forward; expects the color argument to have been made from VGA_makecolor or by some other process that combines the foreground and background colors */
void VGA_putentry(uint8_t character, uint8_t color, size_t x, size_t y); /* puts an entry at a certain part of the screen; expects the color argument to have been made from VGA_makecolor or by some other process that combines the foreground and background colors */
void VGA_putchar(uint8_t character); /* Puts a character at the next spot on the screen; uses VGA_color */  
void VGA_putstring(uint8_t* str); /* Calls VGA_putchar on every entry in the array */ 
void VGA_printf(uint8_t* str, ...); /* Outputs a string and puts a newline in automatically; only supports %s option right now */  
#endif 
