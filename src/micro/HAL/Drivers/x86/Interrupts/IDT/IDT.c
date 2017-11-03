#include <HAL/Drivers/x86/Interrupts/IDT/IDT.h>


static void Interrupt_DumpExceptionStack(interrupt_stackstate thestack) { 
	terminal_printf("\nGS: %h. FS: %h. ES: %h. DS: %h.", thestack.gs, thestack.fs, thestack.es, thestack.ds); 
	terminal_printf("EDI: %h. ESI: %h. EBP: %h. ESP: %h. EBX: %h. ECX: %h. EAX: %h.  ", thestack.edi, thestack.esi, thestack.ebp, thestack.esp, thestack.ebx, thestack.ecx, thestack.eax); 
	terminal_printf("Interrupt_number: %h. Error code: %h.", thestack.interrupt_number, thestack.errorcode); 
	terminal_printf("EIP: %h. CS: %h. EFLAGS: %h. User's esp: %h. SS: %h.", thestack.eip, thestack.cs, thestack.eflags, thestack.useresp, thestack.ss); 
}; 

void Interrupt_Exception_Handler(interrupt_stackstate *stack) { 
	Interrupt_DumpExceptionStack(*stack); 
	panic("Fatal exception!"); 
}; 

void SetIDTEntry(int interruptnum,  uint32_t base, uint16_t theselector, uint8_t flags) { 
	IDT[interruptnum].base_low = (base & 0xFFFF); 
	IDT[interruptnum].base_high = ((base >> 16) & 0xFFFF); 
	IDT[interruptnum].selector = theselector; 
	IDT[interruptnum].alwayssetto0 = 0; 
	IDT[interruptnum].flags = flags; 
}; 


static void IRQ_Handler(interrupt_stackstate *astack) { 
	if ((PIC_get_isr() >> (astack->interrupt_number)) & 0x01) { 
		if (InterruptHandlers[astack->interrupt_number]) { 
			InterruptHandlers[astack->interrupt_number](astack); 
		}; 
		PIC_SendEOI(astack->interrupt_number - 32); 
	}
	else { 
		if ((astack->interrupt_number) > 39) { 
			PIC_SendEOI(0);  
		}; 
	}; 
}; 

void Interrupt_Handler(interrupt_stackstate *thestack) {  
	if (thestack->interrupt_number > 31) { 
		IRQ_Handler(thestack); 
		return; 
	}; 
	InterruptHandlers[thestack->interrupt_number](thestack); 
}; 

void IDT_init(void) { 
	theidtpointer.size = 2047; 
	theidtpointer.base = (uint32_t)(&IDT); 
	SetIDTEntry(0, (uint32_t)ISR_0, 0x08, 0x8E);
	SetIDTEntry(1, (uint32_t)ISR_1, 0x08, 0x8E);
	SetIDTEntry(2, (uint32_t)ISR_2, 0x08, 0x8E);
	SetIDTEntry(3, (uint32_t)ISR_3, 0x08, 0x8E);
	SetIDTEntry(4, (uint32_t)ISR_4, 0x08, 0x8E);
	SetIDTEntry(5, (uint32_t)ISR_5, 0x08, 0x8E);
	SetIDTEntry(6, (uint32_t)ISR_6, 0x08, 0x8E);
	SetIDTEntry(7, (uint32_t)ISR_7, 0x08, 0x8E);
	SetIDTEntry(8, (uint32_t)ISR_8, 0x08, 0x8E);
	SetIDTEntry(9, (uint32_t)ISR_9, 0x08, 0x8E);
	SetIDTEntry(10, (uint32_t)ISR_10, 0x08, 0x8E);
	SetIDTEntry(11, (uint32_t)ISR_11, 0x08, 0x8E);
	SetIDTEntry(12, (uint32_t)ISR_12, 0x08, 0x8E);
	SetIDTEntry(13, (uint32_t)ISR_13, 0x08, 0x8E);
	SetIDTEntry(14, (uint32_t)ISR_14, 0x08, 0x8E);
	SetIDTEntry(15, (uint32_t)ISR_15, 0x08, 0x8E);
	SetIDTEntry(16, (uint32_t)ISR_16, 0x08, 0x8E);
	SetIDTEntry(17, (uint32_t)ISR_17, 0x08, 0x8E);
	SetIDTEntry(18, (uint32_t)ISR_18, 0x08, 0x8E);
	SetIDTEntry(19, (uint32_t)ISR_19, 0x08, 0x8E);
	SetIDTEntry(20, (uint32_t)ISR_20, 0x08, 0x8E);
	SetIDTEntry(21, (uint32_t)ISR_21, 0x08, 0x8E);
	SetIDTEntry(22, (uint32_t)ISR_22, 0x08, 0x8E);
	SetIDTEntry(23, (uint32_t)ISR_23, 0x08, 0x8E);
	SetIDTEntry(24, (uint32_t)ISR_24, 0x08, 0x8E);
	SetIDTEntry(25, (uint32_t)ISR_25, 0x08, 0x8E);
	SetIDTEntry(26, (uint32_t)ISR_26, 0x08, 0x8E);
	SetIDTEntry(27, (uint32_t)ISR_27, 0x08, 0x8E);
	SetIDTEntry(28, (uint32_t)ISR_28, 0x08, 0x8E);
	SetIDTEntry(29, (uint32_t)ISR_29, 0x08, 0x8E);
	SetIDTEntry(30, (uint32_t)ISR_30, 0x08, 0x8E);
	SetIDTEntry(31, (uint32_t)ISR_31, 0x08, 0x8E);
	SetIDTEntry(32, (uint32_t)ISR_32, 0x08, 0x8E);
	SetIDTEntry(33, (uint32_t)ISR_33, 0x08, 0x8E);
	SetIDTEntry(34, (uint32_t)ISR_34, 0x08, 0x8E);
	SetIDTEntry(35, (uint32_t)ISR_35, 0x08, 0x8E);
	SetIDTEntry(36, (uint32_t)ISR_36, 0x08, 0x8E);
	SetIDTEntry(37, (uint32_t)ISR_37, 0x08, 0x8E);
	SetIDTEntry(38, (uint32_t)ISR_38, 0x08, 0x8E);
	SetIDTEntry(39, (uint32_t)ISR_39, 0x08, 0x8E);
	SetIDTEntry(40, (uint32_t)ISR_40, 0x08, 0x8E);
	SetIDTEntry(41, (uint32_t)ISR_41, 0x08, 0x8E);
	SetIDTEntry(42, (uint32_t)ISR_42, 0x08, 0x8E);
	SetIDTEntry(43, (uint32_t)ISR_43, 0x08, 0x8E);
	SetIDTEntry(44, (uint32_t)ISR_44, 0x08, 0x8E);
	SetIDTEntry(45, (uint32_t)ISR_45, 0x08, 0x8E);
	SetIDTEntry(46, (uint32_t)ISR_46, 0x08, 0x8E);
	SetIDTEntry(47, (uint32_t)ISR_47, 0x08, 0x8E);
	int i;
	for (i = 0; i <= 31; i++) { 
		InterruptHandlers[i] = Interrupt_Exception_Handler; 
	}; 
	load_idt(theidtpointer); 
}; 
