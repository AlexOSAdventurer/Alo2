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
		PIC_SendEOI(astack->interrupt_number - 32); 
		if (InterruptHandlers[astack->interrupt_number]) { 
			InterruptHandlers[astack->interrupt_number](astack); 
		}; 
	}
	else { 
		if ((astack->interrupt_number) > 39) { 
			PIC_SendEOI(0);  
		}; 
	}; 
}; 

void Interrupt_Handler(interrupt_stackstate *thestack) {  
	if ((thestack->interrupt_number > 31) && (thestack->interrupt_number < 48)) { 
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
	SetIDTEntry(48, (uint32_t)ISR_48, 0x08, 0x8E);
	SetIDTEntry(49, (uint32_t)ISR_49, 0x08, 0x8E);
	SetIDTEntry(50, (uint32_t)ISR_50, 0x08, 0x8E);
	SetIDTEntry(51, (uint32_t)ISR_51, 0x08, 0x8E);
	SetIDTEntry(52, (uint32_t)ISR_52, 0x08, 0x8E);
	SetIDTEntry(53, (uint32_t)ISR_53, 0x08, 0x8E);
	SetIDTEntry(54, (uint32_t)ISR_54, 0x08, 0x8E);
	SetIDTEntry(55, (uint32_t)ISR_55, 0x08, 0x8E);
	SetIDTEntry(56, (uint32_t)ISR_56, 0x08, 0x8E);
	SetIDTEntry(57, (uint32_t)ISR_57, 0x08, 0x8E);
	SetIDTEntry(58, (uint32_t)ISR_58, 0x08, 0x8E);
	SetIDTEntry(59, (uint32_t)ISR_59, 0x08, 0x8E);
	SetIDTEntry(60, (uint32_t)ISR_60, 0x08, 0x8E);
	SetIDTEntry(61, (uint32_t)ISR_61, 0x08, 0x8E);
	SetIDTEntry(62, (uint32_t)ISR_62, 0x08, 0x8E);
	SetIDTEntry(63, (uint32_t)ISR_63, 0x08, 0x8E);
	SetIDTEntry(64, (uint32_t)ISR_64, 0x08, 0x8E);
	SetIDTEntry(65, (uint32_t)ISR_65, 0x08, 0x8E);
	SetIDTEntry(66, (uint32_t)ISR_66, 0x08, 0x8E);
	SetIDTEntry(67, (uint32_t)ISR_67, 0x08, 0x8E);
	SetIDTEntry(68, (uint32_t)ISR_68, 0x08, 0x8E);
	SetIDTEntry(69, (uint32_t)ISR_69, 0x08, 0x8E);
	SetIDTEntry(70, (uint32_t)ISR_70, 0x08, 0x8E);
	SetIDTEntry(71, (uint32_t)ISR_71, 0x08, 0x8E);
	SetIDTEntry(72, (uint32_t)ISR_72, 0x08, 0x8E);
	SetIDTEntry(73, (uint32_t)ISR_73, 0x08, 0x8E);
	SetIDTEntry(74, (uint32_t)ISR_74, 0x08, 0x8E);
	SetIDTEntry(75, (uint32_t)ISR_75, 0x08, 0x8E);
	SetIDTEntry(76, (uint32_t)ISR_76, 0x08, 0x8E);
	SetIDTEntry(77, (uint32_t)ISR_77, 0x08, 0x8E);
	SetIDTEntry(78, (uint32_t)ISR_78, 0x08, 0x8E);
	SetIDTEntry(79, (uint32_t)ISR_79, 0x08, 0x8E);
	SetIDTEntry(80, (uint32_t)ISR_80, 0x08, 0x8E);
	SetIDTEntry(81, (uint32_t)ISR_81, 0x08, 0x8E);
	SetIDTEntry(82, (uint32_t)ISR_82, 0x08, 0x8E);
	SetIDTEntry(83, (uint32_t)ISR_83, 0x08, 0x8E);
	SetIDTEntry(84, (uint32_t)ISR_84, 0x08, 0x8E);
	SetIDTEntry(85, (uint32_t)ISR_85, 0x08, 0x8E);
	SetIDTEntry(86, (uint32_t)ISR_86, 0x08, 0x8E);
	SetIDTEntry(87, (uint32_t)ISR_87, 0x08, 0x8E);
	SetIDTEntry(88, (uint32_t)ISR_88, 0x08, 0x8E);
	SetIDTEntry(89, (uint32_t)ISR_89, 0x08, 0x8E);
	SetIDTEntry(90, (uint32_t)ISR_90, 0x08, 0x8E);
	SetIDTEntry(91, (uint32_t)ISR_91, 0x08, 0x8E);
	SetIDTEntry(92, (uint32_t)ISR_92, 0x08, 0x8E);
	SetIDTEntry(93, (uint32_t)ISR_93, 0x08, 0x8E);
	SetIDTEntry(94, (uint32_t)ISR_94, 0x08, 0x8E);
	SetIDTEntry(95, (uint32_t)ISR_95, 0x08, 0x8E);
	SetIDTEntry(96, (uint32_t)ISR_96, 0x08, 0x8E);
	SetIDTEntry(97, (uint32_t)ISR_97, 0x08, 0x8E);
	SetIDTEntry(98, (uint32_t)ISR_98, 0x08, 0x8E);
	SetIDTEntry(99, (uint32_t)ISR_99, 0x08, 0x8E);
	int i;
	for (i = 0; i <= 31; i++) { 
		InterruptHandlers[i] = Interrupt_Exception_Handler; 
	}; 
	for (i = 48; i <= 99; i++) { 
		InterruptHandlers[i] = Interrupt_Exception_Handler; 
	};
	load_idt(theidtpointer); 
}; 
