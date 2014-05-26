.global load_gdt 

.type load_gdt, @function 


load_gdt: 
	movw 8(%esp),  %edx  
	lgdt 12(%esp) 
	movw 4(%esp), %ax 
	movl %ax, %ds 
	movl %ax, %es 
	movl %ax, %fs 
	movl %ax, %gs 
	movl %ax, %ss 
	jmp %edx:headback 
	headback: 
		ret 

