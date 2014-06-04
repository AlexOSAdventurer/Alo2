CC=i386-elf-gcc 
AS=i386-elf-as 
CFLAGS= -c -Wall -O2 -std=gnu99 -Wextra -I/home/Alex/githubdir/Alo2/include 
LDFLAGS= -T build/ALinkScript.ld -ffreestanding -O2 -nostdlib -lgcc -g
CSOURCES=src/HAL/Drivers/TextModeVGA/TextModeVGA.c src/Utility/Utility.c src/Kernel/Main.c src/HAL/Interactors/Terminal/Terminal.c src/HAL/hal.c src/HAL/Drivers/x86/GDT/GDT.c src/HAL/Drivers/x86/Interrupts/PIC/PIC.c src/HAL/Drivers/x86/Interrupts/IDT/IDT.c src/HAL/Drivers/x86/Interrupts/Interrupts.c src/HAL/Drivers/x86/PIT/PIT.c src/HAL/Interactors/Timer/Timer.c  
ASOURCES= src/Utility/AssemblyStuff.s  src/Kernel/Multibootheader.s src/Kernel/EntryPoint.s src/HAL/Drivers/x86/GDT/GDTAssembly.s src/HAL/Drivers/x86/Interrupts/IDT/InterruptAssembly.s 
OBJECTS=$(CSOURCES:.c=.o) $(ASOURCES:.s=.o) 
EXECUTABLE=build/isodir/boot/Alo2.bin 

clean: 
	rm $(OBJECTS) 

all: $(OBJECTS) $(EXECUTABLE) 
	grub-mkrescue --output=build/Alo2.iso build/isodir
	
$(EXECUTABLE): $(OBJECTS) 
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@ 
	
.c.o:
	$(CC) $(CFLAGS) $< -o $@

.s.o: 
	$(AS) $< -o $@ 

	