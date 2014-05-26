#pragma once 

#include <stdint-gcc.h> 
#include <stddef.h> 

static uint16_t* TextModeVGA_Buffer = 0xB8000; 
static const size_t TextModeVGA_Width = 80; 
static const size_t TextModeVGA_Height = 24; 


typedef enum VGA_color_t { 
	BLACK, BLUE, GREEN, CYAN, RED, MAGENTA, BROWN, LIGHT_GREY, DARK_GREY, LIGHT_BLUE, LIGHT_GREEN, LIGHT_CYAN, LIGHT_RED, LIGHT_MAGENTA, LIGHT_BROWN, WHITE 
} VGA_color; 

static uint8_t generate_color(VGA_color foreground, VGA_color background); 

static uint16_t make_entry(char character, uint8_t  color); 

void TextModeVGA_putentry(char c, VGA_color foreground,  VGA_color background, size_t x, size_t y); 
