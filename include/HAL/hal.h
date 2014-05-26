#pragma once 

#include <HAL/Drivers/TextModeVGA/TextModeVGA.h> 
#include <GRUB/multiboot.h> 
#include <Utility/Utility.h> 


void HAL_init(multiboot_info_t *multibootinfo); 

