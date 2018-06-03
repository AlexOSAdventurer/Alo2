#pragma once 
#include <stdint-gcc.h> 

typedef struct __attribute__((packed)) { 
	uint32_t tablesize; 
	uint32_t stringsize; 
	uint32_t address; 
	uint32_t reserv; 
} aout_symbols; 

typedef struct __attribute__((packed)) { 
	uint32_t number; 
	uint32_t size; 
	uint32_t address; 
	uint32_t shnd; 
} elf_symbols; 

typedef struct __attribute__((packed)) { 
	uint32_t mod_start;
	uint32_t mod_end;
	const char* string;
	uint32_t reserved; 
} multiboot_modules;

typedef union { 
	aout_symbols aout; 
	elf_symbols elf; 
} multiboot_symbols; 




typedef struct __attribute__((packed)) { 
	uint32_t flags; 
	uint32_t lowermemory; 
	uint32_t highermemory; 
	uint32_t thebootdevice; 
	uint32_t commandlineargs; 
	uint32_t numberofmodules; 
	multiboot_modules* modules; 
	multiboot_symbols symbols; 
	uint32_t memorymap_length; 
	uint32_t memorymap_address; 
	uint32_t drives_length; 
	uint32_t drives_address; 
	uint32_t configuration_table; 
	uint32_t nameeofbootloader; 
	uint32_t apm_table; 
	uint32_t vbe_control_information; 
	uint32_t vbe_mode_information; 
	uint16_t vbe_mode; 
	uint16_t vbe_interface_segment; 
	uint16_t vbe_interface_off; 
	uint16_t vbe_interface_length; 
	uint64_t framebuffer_address; 
	uint32_t framebuffer_pitch; 
	uint32_t framebuffer_width; 
	uint32_t framebuffer_height; 
	uint8_t fraembuffer_bpp; 
	uint8_t framebuffer_type; 
	uint64_t color_information;  
} multiboot_data; 
