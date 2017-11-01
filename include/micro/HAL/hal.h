#pragma once 

#include <HAL/Drivers/TextModeVGA/TextModeVGA.h> 
#include <GRUB/multiboot.h> 
#include <Utility/Utility.h> 
#include <HAL/Drivers/x86/GDT/GDT.h> 
#include <HAL/Drivers/x86/Interrupts/Interrupts.h> 
#include <HAL/Drivers/x86/Paging/paging.h>
#include <HAL/Interactors/Timer/Timer.h> 
#include <HAL/Interactors/DateAndTime/DateAndTime.h> 
#include <Memory/kmalloc_nfree.h>
#include <Memory/kmalloc.h>


void HAL_init(multiboot_data *multibootinfo); 

