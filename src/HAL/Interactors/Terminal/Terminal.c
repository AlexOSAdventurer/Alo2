#include <HAL/Interactors/Terminal/Terminal.h> 

static const size_t terminal_height = 25; 
static const size_t terminal_width = 80; 

static size_t terminal_currentx = 0; 
static size_t terminal_currenty = 0; 


static terminal_color terminal_currentforeground = GREEN;  

static terminal_color terminal_currentbackground = BLACK; 

/* Just makes the screen go black */  
void terminal_init(void) { 
	for (int yi = 0; yi < terminal_height; yi++) { 
		for (int xi = 0; xi < terminal_width; xi++) { 
			TextModeVGA_putentry(' ', BLACK, BLACK, xi, yi); 
		}; 
	}; 
}; 

void terminal_putchar(char character, terminal_color background, terminal_color foreground) { 
	if (character == '\n') { 
		if (terminal_currenty == (terminal_height - 1)) { 
			terminal_currenty = 0; 
		} 
		else { 
			terminal_currenty++; 
		}; 
		terminal_currentx = 0; 
		terminal_movecursor(1, terminal_currenty); 
		return; 
	}; 
	if (terminal_currentx == (terminal_width - 1)) { 
		terminal_putchar('\n', BLACK, BLACK); 
	}; 		
	TextModeVGA_putentry(character, foreground, background, terminal_currentx, terminal_currenty); 
	if (terminal_currentx == (terminal_width - 2)) { 
		terminal_movecursor(0, terminal_currenty + 1); 
	} 
	else { 
		terminal_movecursor(terminal_currentx + 1, terminal_currenty); 
	}; 
	terminal_currentx++; 
}; 

void terminal_putstring(const char* str) { 
	for (int i = 0; str[i] != 0; i++) { 
		terminal_putchar((char)str[i], terminal_currentbackground, terminal_currentforeground); 
	}; 
}; 

/* TODO: Migrate this into the TextModeVGA driver */ 
	
void terminal_movecursor(int x, int  y) { 
	uint16_t theposition = (y * terminal_width) + x; 

	outportb(0x3D4, 0x0E); 

	io_wait(); 

	outportb(0x3D5, (uint8_t) (theposition >> 8)); 
	io_wait(); 

	outportb(0x3D4, 0x0F); 
	io_wait(); 
	outportb(0x3D5,  (uint8_t)(theposition)); 
	
	io_wait(); 
}; 

void terminal_printf(const char *str, ...) { 
	va_list thelist; 
	va_start(thelist, str); 
	for (int i = 0; str[i] != NULL; i++) { 
		if (str[i] == '%') { 
			if (str[i + 1] == 's') { 
				terminal_putstring(va_arg(thelist, const char*)); 
			} 
			else if (str[i + 1] == 'd') {
				char thebuffer[256]; 
				itoa(va_arg(thelist, int), thebuffer, 10); 
				terminal_putstring(thebuffer); 
			} 
			else if (str[i + 1] == '%') { 
				terminal_putchar('%', terminal_currentbackground, terminal_currentforeground); 
			}
			else { 
				terminal_putchar('%', terminal_currentbackground, terminal_currentforeground); 
				terminal_putchar((char)str[i + 1], terminal_currentbackground, terminal_currentforeground); 
			}; 
			i++; 
		} 
		else { 
			terminal_putchar(str[i], terminal_currentbackground, terminal_currentforeground); 
		}; 
	}; 
	terminal_putchar('\n', terminal_currentbackground, terminal_currentforeground); 
	va_end(thelist); 
}; 	