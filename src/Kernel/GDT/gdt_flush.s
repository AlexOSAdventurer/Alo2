.intel_syntax noprefix 

.global assign_gdt
.type assign_gdt, @function 
assign_gdt: 
	lgdt [esp + 4] # should load our GDT ptr! 
	mov ax, 0x10
	mov ds, ax 
	mov es, ax
	mov fs, ax
	mov gs, ax  
	mov ss, ax 
	jmp 0x08:Section2 
Section2: 

	ret 

