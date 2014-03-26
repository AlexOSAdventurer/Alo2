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


void VGA_init(); 
void VGA_movecursor(size_t x, size_t y); 
void VGA_setcolor(uint8_t color); 
void VGA_putentry(uint8_t character, uint8_t color, size_t x, size_t y); 
void VGA_putchar(uint8_t character); 
void VGA_putstring(uint8_t* str); 
void VGA_printf(uint8_t* str, ...); 
#endif 
