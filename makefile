CC=../CrossCompiler/GCC/bin/i386-elf-gcc 
ASM=../CrossCompiler/GCC/bin/i386-elf-as
CFLAGS= -c -Wall -O2 -std=gnu99 -Wextra -g -Wunused-parameter
LDFLAGS= -T build/linker.ld -ffreestanding -O2 -nostdlib -lgcc -g 

CSOURCES=src/Kernel/BasicVGA/BasicVGA.c src/Kernel/Main.c src/Kernel/Ports/Port.c src/Kernel/GDT/GDT.c src/Kernel/Interrupts/IDT/idt.c src/Kernel/Interrupts/ISR/isr.c 

ASOURCES=src/Kernel/AssemblyEntryPoint.s src/Kernel/GDT/gdt_flush.s src/Kernel/Interrupts/IDT/load_idt.s src/Kernel/Interrupts/ISR/israsmhandlers.s 

COBJECTS=$(CSOURCES:.c=.o) 
AOBJECTS=$(ASOURCES:.s=.o)
EXECUTABLE=build/Alo2.bin 

all: $(CSOURCES) $(EXECUTABLE) 
	cp build/Alo2.bin isodir/boot/Alo2.bin 
	grub-mkrescue --output=build/Alo2.iso isodir
	
$(EXECUTABLE): $(COBJECTS) $(AOBJECTS)
	$(CC) $(LDFLAGS) $(COBJECTS) $(AOBJECTS) -o $@

.c.o:
	$(CC) $(CFLAGS) $< -o $@

.s.o: 
	$(ASM) $< -o $@
