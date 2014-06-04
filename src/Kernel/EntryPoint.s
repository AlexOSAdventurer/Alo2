.section .MainStack, "aw", @nobits 
stack_bottom: 
.skip 32768 # 32 kilobyte stack 
stack_top:  

.section .text 
.global _KernelEntry  
.type _KernelEntry, @function 
_KernelEntry: 
		movl $stack_top, %esp 
		push %ebx 
		call Alo_Main 
		pop %ebx 
		.InfiniteJumpLoop: 
			jmp .InfiniteJumpLoop 
