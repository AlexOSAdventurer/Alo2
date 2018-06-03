EM=qemu-system-i386
DS=i686-elf-objdump

DISASSEMBLE_FILE=disassembly-kernel.txt
EXECUTABLE=build/isodir/boot/Alo2.bin 
TARGETISO=build/Alo2.iso 
ISODIR=build/isodir 


.PHONY: emulator clean 
	
all:
	make -C src all 
	grub-mkrescue --output=$(TARGETISO)  $(ISODIR) 


emulator: $(TARGETISO) 
	$(EM) $(TARGETISO) -s & 
	gdb $(EXECUTABLE) -ex "target remote localhost:1234"

disassemble: 
	@$(DS) -d -Matt $(EXECUTABLE) > $(DISASSEMBLE_FILE)
	
clean: 
	@rm -r $(EXECUTABLE) $(TARGETISO) $(DISASSEMBLE_FILE) 2>/dev/null || true
	make -C src clean 
	
	
