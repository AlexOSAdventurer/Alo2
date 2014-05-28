
Reload_CS: 
	retf 

.global load_gdt 

.type load_gdt, @function 


load_gdt: 
	xor %edx, %edx 
	movw 16(%esp), %dx 
	movw 12(%esp), %ax 
	lgdt 4(%esp) 
	movw  %ax, %ds 
	movw %ax, %es 
	movw %ax, %fs 
	movw %ax, %gs 
	movw %ax, %ss 
	push %edx 
	call Reload_CS 
	ret 
	
	