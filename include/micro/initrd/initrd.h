#ifndef INITRD_H
#define INITRD_H 

#include <GRUB/multiboot.h>

void initrd_relocate(multiboot_data* multibootdata);
void initrd_load(multiboot_data* multibootdata);


#endif
