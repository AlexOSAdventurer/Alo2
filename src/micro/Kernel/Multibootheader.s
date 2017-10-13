#First section, eh? 
.section .multiboot 
	.align 4 
	.long 0x1BADB002 
	.long (1<<0) | (1<<1)  
	.long -(0x1BADB002 + ((1<<0) | (1<<1))) 
	
