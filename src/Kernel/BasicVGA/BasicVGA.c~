#include "../../../include/Kernel/BasicVGA/BasicVGA.h" 

/* We could make it so there are more bits for both the background and foreground colors. However, that would require a general VGA driver to do, and I am not that knowledgeable yet :( */

uint8_t make_color(VGA_color_val foreground, VGA_color_val background) { 
	return foreground | (background << 4); /* The background bits take up the four most significant bits, with the foreground taking the four least signficant ones. */
}; 

uint16_t make_vgaentry(uint8_t c, uint8_t color) { 
	uint16_t c16 = c;  
	uint16_t color16 = color; 
	return c16 | (color16 << 8); 
}; 

size_t strlen(uint8_t* str) {
	size_t res = 0; 
	while (str[res] != 0) { 
		res++; 
	}; 
	return res; 
}; 


void VGA_init() { 
	VGA_row = 0; 
	VGA_column = 0; 
	VGA_color = make_color(COLOR_GREEN, COLOR_BLACK); 
	VGA_buffer = (uint16_t*)0xB8000; /* The address of the VGA buffer */
	for (size_t y = 0;y < VGA_HEIGHT; y++) { 
		for (size_t x = 0; x < VGA_WIDTH; x++) { 
			VGA_putentry(' ', VGA_color, x, y); 
		}; 
	}; 
}; 

void VGA_movecursor(size_t x, size_t y) { 
	uint16_t location = (y * VGA_WIDTH) + x; 
	outportb(0x3D4, 0x0F); 
	io_wait(); 
	outportb(0x3D5, (uint8_t)(location &0xFF)); 
	io_wait(); 
	outportb(0x3D4, 0x0E); 
	io_wait(); 
	outportb(0x3D5, (uint8_t)((location >> 8)&0xFF)); 
	io_wait(); 
}; 
	
void VGA_setcolor(uint8_t color) { 
	VGA_color = color; 
}; 

void VGA_putentry(uint8_t character, uint8_t color, size_t x, size_t y) { 
	VGA_buffer[(y * VGA_WIDTH) + x] = make_vgaentry(character, color); 
}; 

void VGA_putchar(uint8_t character) { 
	if (VGA_column++ == VGA_WIDTH) { 
		VGA_putchar('\n'); 
	}; 
	if (character == '\n') { 
		VGA_column = 0; 
		if (VGA_row++ == VGA_HEIGHT) { 
			VGA_row = 0; 
		}; 
	} 
	else { 
		VGA_buffer[(VGA_row * VGA_WIDTH) + VGA_column] = make_vgaentry(character, VGA_color); 
	}; 
	VGA_movecursor(VGA_column + 1, VGA_row);  
}; 

void VGA_putstring(uint8_t* str) { 
	size_t i = 0; 
	while (str[i] != NULL) { 
		VGA_putchar(str[i]); 
		i++; 
	}; 
}; 

void VGA_printf(uint8_t* str, ...) { 
	size_t stringlength = strlen(str); 
	va_list arglist; 
	va_start(arglist, str); 
	for (size_t i = 0; i < stringlength; i++) { 
		if (str[i] == '%') { 
			if (str[i + 1] == 's') {  
				VGA_putstring(va_arg(arglist, uint8_t*)); 
				i++;
			} 
			else { 
				VGA_putchar('%'); 
			}; 
		} 
		else { 
			VGA_putchar(str[i]); 
		}; 
	}; 
	VGA_putchar('\n'); 
	va_end(arglist); 
}; 

