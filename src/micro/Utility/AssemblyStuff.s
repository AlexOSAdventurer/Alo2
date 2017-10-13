.global outportb 
.type outportb, @function 

outportb: 
	movw 4(%esp), %dx 
	movb 8(%esp), %al 
	outb %al,  %dx   
	ret 

.global inportb 
.type inportb, @function 

inportb: 
	xor %eax, %eax 
	movw 4(%esp), %dx     
	inb %dx, %al      
	ret 

.global io_wait 
.type inportb, @function 

io_wait: 
	outb %al, $80 
	ret 

