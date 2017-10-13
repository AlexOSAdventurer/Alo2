ENTRY(_KernelEntry) 

SECTIONS { 
	. = 1M; 
	.text BLOCK(4k) : ALIGN(4k) { 
		*(.multiboot) 
		*(.text) 
	} 
	
	.rodata BLOCK(4K)  :  ALIGN(4K) { 
		*(.rodata) 
	} 
	
	.data BLOCK(4K) : ALIGN(4K) 
	{ 
		*(.data) 
	} 
	
	.bss BLOCK(4K)    :          ALIGN(4K) { 
		*(COMMON) 
		*(.bss) 
		*(.MainStack) 
	} 
	
	_kmalloc_nfree_addr = .;

} 

