.global paging_enable 
.type paging_enable, @function 
	
paging_enable: 
	movl %cr0, %eax 
	orl $0x80000000, %eax
	movl %eax, %cr0 
	ret 
	
.global paging_disable 
.type paging_disable, @function 
	
paging_disable: 
	movl %cr0, %eax 
	andl $0x7FFFFFFF, %eax
	movl %eax, %cr0 
	ret 
	
.global paging_load_dir
.type paging_load_dir, @function 

paging_load_dir: 
	movl 4(%esp), %eax
	movl %eax, %cr3 
	ret
	
