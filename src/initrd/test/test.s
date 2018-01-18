loop: 
	mov $_str, %edx 
	mov $1, %eax 
	int $0x30
	inc %ecx
	int $0x30
	jmp loop
	
	
	
_str:
	.string "Yielded once."
	
