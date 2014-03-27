Alo2
====

Background 
---- 
If you don't want to listen to a whole bunch of gab largely unrelated to the OS, skip to the next section! 


A couple of years back, I got interested in low-level parts of computer systems. 
I had originally worked on user-level applications, but I found that they were about a tenth as gratifying as working on a bare bones computer. 

Don't ask why. 

Around the summer, of 2013, I decided to write an OS. Not a complex one; I just wanted to see how far I could go. However, due partly to the fact that I knew little about low-level debugging (gdb, had I known you, you would have been my best friend), and that school was starting back up, I ditched the project. It know exists as the Alo repository of mine; if anyone can make something out of it, more power to them. Now, with school winding down in a couple of months, and the fact that I had five days of vacation and nothing to do in the mean-time, I decided to take another stab at it! 


The OS 
----



Status
----
As it stands, I haven't gotten very far; I can't even read from the keyboard properly yet (through hardware interrupts). That should change very soon though. I DO have the GDT and IDT set up, and can catch processor exceptions. 
Only supports 386+ processors! (However, basically every modern PC falls under that)

Usage 
---- 
As it is, you should change to the main directory of the repository and simply do a "make all", in which you will find an Alo2.iso file in the build directory, ready to boot! 

Dependencies 
---- 
You will need GCC and binutils; they will need to target i386-elf. You will have to tweak the makefile so it uses the compiler and assembler you want it to use; sorry if that is a little bit of a pain! In addition, you will have to make sure you got the GRUB utility programs installed, as the makefile uses grub-mkrescue to make an iso image! 

Caveats 
---- 
* Only tested with qemu! 

* You need to manually delete all object files after a build to ensure that the next build will be completely fresh (sorry; I am just not good with makefiles yet!)  

* When you add to it, when you add an include directive, you will have to use the "../" a few times to get out into the main directory, and THEN go to the include directory! 


