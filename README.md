Alo2
====

Background 
---- 
GOAL:  Get as far as I can!!!!!!!!!!!!!!!!!!!!  

The OS 
----



Status
---- 
I have video output set up, along with interrupts and the PIT (which is set at 100 hz). 
Only supports 386+ processors! (However, basically every modern PC falls under that)

Usage 
---- 
As it is, you should change to the main directory of the repository and simply do a "make all", in which you will find an Alo2.iso file in the build directory, ready to boot! 

To clean out all object files, just do a make clean. 

Dependencies 
---- 
You will need a GCC cross compiler that targets i386-elf and add its bin directory to the PATH variable (you need to be using Cygwin or a *NIX like OS).  Otherwise, my makefile is most likely useless to you; sorry if that is a little bit of a pain! In addition, you will have to make sure you got the GRUB2 utility programs installed, as the makefile uses grub-mkrescue to make an iso image! 

Caveat  
---- 
* Only tested with qemu and bochs! 

