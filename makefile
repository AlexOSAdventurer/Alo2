CC=i386-elf-gcc 
AS=i386-elf-as 
CFLAGS= -c -Wall -O2 -std=gnu99 -Wextra -I/home/alex/Desktop/Alo4/include 
LDFLAGS= -T build/ALinkScript.ld -ffreestanding -O2 -nostdlib -lgcc -g
CSOURCES=src/HAL/Drivers/TextModeVGA/TextModeVGA.c src/Utility/Utility.c src/Kernel/Main.c src/HAL/Interactors/Terminal/Terminal.c src/HAL/hal.c 
ASOURCES= src/Utility/AssemblyStuff.s  src/Kernel/Multibootheader.s src/Kernel/EntryPoint.s
OBJECTS=$(CSOURCES:.c=.o) $(ASOURCES:.s=.o) 
EXECUTABLE=build/isodir/boot/Alo2.bin 

clean: 
	rm $(OBJECTS) 

all: $(CSOURCES) $(EXECUTABLE) 
	grub-mkrescue --output=build/Alo2.iso build/isodir
	
$(EXECUTABLE): $(OBJECTS) 
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@ 
	
.c.o:
	$(CC) $(CFLAGS) $< -o $@

.s.o: 
	$(AS) $< -o $@ 

	