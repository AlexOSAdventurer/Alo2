#ifndef HAL_H
#define HAL_H

#include <gcc-lib-funcs/gcc-lib-funcs.h>
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
#include <Task/task.h>
#include <Process/process.h>
#include <system-lib/system_lib.h>
#include <initrd/initrd.h>

void HAL_init(multiboot_data *multibootinfo); 


#endif
