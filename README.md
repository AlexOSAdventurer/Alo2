Alo2
====

Background 
---- 
GOAL:  Get as far as I can!!!!!!!!!!!!!!!!!!!!  

The OS 
----



Status
---- 
As it stands, I haven't gotten very far; I can't even read from the keyboard properly yet (through hardware interrupts). That should change very soon though. I DO have the GDT and IDT set up, and can catch processor exceptions. 
Only supports 386+ processors! (However, basically every modern PC falls under that)

Usage 
---- 
As it is, you should change to the main directory of the repository and simply do a "make all", in which you will find an Alo2.iso file in the build directory, ready to boot! 

To clean out all object files, just do a make clean. 

Dependencies 
---- 
You will need GCC and binutils; they will need to target i386-elf. You will have to tweak the makefile so it uses the compiler and assembler you want it to use; sorry if that is a little bit of a pain! In addition, you will have to make sure you got the GRUB2 utility programs installed, as the makefile uses grub-mkrescue to make an iso image! 

Caveat  
---- 
* Only tested with qemu! 

