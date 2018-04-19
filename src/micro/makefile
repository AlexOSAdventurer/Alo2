CC=i686-elf-gcc 
AS=i686-elf-as 
RT=../..
CINCLUDE=$(RT)/include/micro
CFLAGS= -c -Wall -O3 -ffreestanding -std=gnu99 -Wextra -I$(CINCLUDE) -ggdb
LDFILE=$(RT)/build/ALinkScript.ld
LDFLAGS= -T $(LDFILE) -ffreestanding -O3  -nostdlib -lgcc -ggdb


CSOURCES := $(shell find . -name '*.c')
ASOURCES := $(shell find . -name '*.s')
OBJECTS  := $(CSOURCES:.c=.o) $(ASOURCES:.s=.o) 

EXECUTABLE = Alo2.bin
EXECUTABLE_L = ../../build/isodir/boot/$(EXECUTABLE)

.PHONY: all build

all: $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS) 
	$(CC) -o $(EXECUTABLE_L) $(LDFLAGS) $^
	
	
%.o: %.c
	$(CC) $(CFLAGS) $< -o $@
	
%.o: %.s
	$(AS) $< -o $@ 

clean: 
	@rm -r $(OBJECTS) $(EXECUTABLE_L) 2>/dev/null || true
