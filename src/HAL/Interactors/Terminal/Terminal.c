#include <HAL/Interactors/Terminal/Terminal.h> 

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