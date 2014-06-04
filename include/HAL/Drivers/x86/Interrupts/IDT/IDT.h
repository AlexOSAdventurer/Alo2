#pragma once 

#include <HAL/Drivers/x86/Interrupts/PIC/PIC.h>
#include <Utility/Utility.h>
#include <stdint-gcc.h> 

typedef struct __attribute__((packed)) { 
	uint32_t gs, fs, es, ds; 
	uint32_t edi, esi, ebp, esp, ebx, edx, ecx, eax; 
	uint32_t interrupt_number, errorcode; 
	uint32_t eip, cs, eflags, useresp, ss; 
} interrupt_stackstate; 

typedef struct __attribute__((packed)) { 
	uint16_t base_low; 
	uint16_t selector; 
	uint8_t alwayssetto0; 
	uint8_t flags; 
	uint16_t base_high; 
} IDT_entry; 

typedef struct __attribute__((packed)) { 
	uint16_t size; 
	uint32_t base; 
} IDT_pointer; 


void ISR_0(void); 
void ISR_1(void); 
void ISR_2(void); 
void ISR_3(void); 
void ISR_4(void); 
void ISR_5(void); 
void ISR_6(void); 
void ISR_7(void); 
void ISR_8(void); 
void ISR_9(void); 
void ISR_10(void); 
void ISR_11(void); 
void ISR_12(void); 
void ISR_13(void); 
void ISR_14(void); 
void ISR_15(void); 
void ISR_16(void); 
void ISR_17(void); 
void ISR_18(void); 
void ISR_19(void); 
void ISR_20(void); 
void ISR_21(void); 
void ISR_22(void); 
void ISR_23(void); 
void ISR_24(void); 
void ISR_25(void); 
void ISR_26(void); 
void ISR_27(void); 
void ISR_28(void); 
void ISR_29(void); 
void ISR_30(void); 
void ISR_31(void); 
void ISR_32(void); 
void ISR_33(void); 
void ISR_34(void); 
void ISR_35(void); 
void ISR_36(void); 
void ISR_37(void); 
void ISR_38(void); 
void ISR_39(void); 
void ISR_40(void); 
void ISR_41(void); 
void ISR_42(void); 
void ISR_43(void); 
void ISR_44(void); 
void ISR_45(void); 
void ISR_46(void); 
void ISR_47(void); 


IDT_entry IDT[256]; 

IDT_pointer theidtpointer; 

typedef void (*interrupthandlerfunc)(interrupt_stackstate*); 

interrupthandlerfunc InterruptHandlers[256]; 

void Interrupt_Exception_Handler(interrupt_stackstate *stack); 

void SetIDTEntry(int interruptnum,  uint32_t base, uint16_t theselector, uint8_t flags); 

void Interrupt_Handler(interrupt_stackstate *thestack); 

void  load_idt(IDT_pointer ourpointer); 

void IDT_init(void); 

