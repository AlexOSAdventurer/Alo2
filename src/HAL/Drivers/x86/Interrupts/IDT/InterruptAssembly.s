.macro InterruptHandlerPushDummy interruptnum 
	.global ISR_\interruptnum 
	.type ISR_\interruptnum , @function 
	ISR_\interruptnum: 
		cli
		push $0 
		push $\interruptnum 
		jmp MainInterruptPiece 
		
		
		
		
.endm 
	
.macro InterruptHandlerErrorCode interruptnum 
	.global ISR_\interruptnum 
	.type ISR_\interruptnum , @function 
	ISR_\interruptnum: 
		cli
		push $\interruptnum 
		jmp MainInterruptPiece 
		
		
		
	
.endm 



InterruptHandlerPushDummy 0 
InterruptHandlerPushDummy 1 
InterruptHandlerPushDummy 2 
InterruptHandlerPushDummy 3 
InterruptHandlerPushDummy 4 
InterruptHandlerPushDummy 5 
InterruptHandlerPushDummy 6 
InterruptHandlerPushDummy 7 
InterruptHandlerErrorCode 8 
InterruptHandlerPushDummy 9 
InterruptHandlerErrorCode 10 
InterruptHandlerErrorCode 11 
InterruptHandlerErrorCode 12 
InterruptHandlerErrorCode 13 
InterruptHandlerErrorCode 14 
InterruptHandlerPushDummy 15 
InterruptHandlerPushDummy 16 
InterruptHandlerPushDummy 17 
InterruptHandlerPushDummy 18 
InterruptHandlerPushDummy 19 
InterruptHandlerPushDummy 20 
InterruptHandlerPushDummy 21 
InterruptHandlerPushDummy 22 
InterruptHandlerPushDummy 23 
InterruptHandlerPushDummy 24 
InterruptHandlerPushDummy 25 
InterruptHandlerPushDummy 26 
InterruptHandlerPushDummy 27 
InterruptHandlerPushDummy 28 
InterruptHandlerPushDummy 29 
InterruptHandlerPushDummy 30 
InterruptHandlerPushDummy 31 
InterruptHandlerPushDummy 32 
InterruptHandlerPushDummy 33 
InterruptHandlerPushDummy 34 
InterruptHandlerPushDummy 35 
InterruptHandlerPushDummy 36  
InterruptHandlerPushDummy 37 
InterruptHandlerPushDummy 38 
InterruptHandlerPushDummy 39 
InterruptHandlerPushDummy 40 
InterruptHandlerPushDummy 41 
InterruptHandlerPushDummy 42 
InterruptHandlerPushDummy 43 
InterruptHandlerPushDummy 44 
InterruptHandlerPushDummy 45 
InterruptHandlerPushDummy 46 
InterruptHandlerPushDummy 47 
 
MainInterruptPiece: 
	.intel_syntax noprefix 
		pushad 
	.att_syntax prefix 
	push %ds 
	push %es 
	push %fs 
	push %gs 
	mov $0x10, %ax 
	mov %ax, %ds 
	mov %ax, %es 
	mov %ax, %fs 
	mov %ax, %gs 
	push %esp 
	call Interrupt_Handler 
	pop %eax 
	pop %gs 
	pop %fs 
	pop %es 
	pop %ds
	.intel_syntax noprefix 
		popad 
	.att_syntax prefix 
	add $8, %esp 
	sti
	iret 
	
.global load_idt 
.type load_idt, @function 
	
load_idt: 
	lidt 4(%esp) 
	ret 
	

	