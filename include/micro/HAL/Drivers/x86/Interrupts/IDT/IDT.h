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
void ISR_48(void);
void ISR_49(void);
void ISR_50(void); 
void ISR_51(void); 
void ISR_52(void); 
void ISR_53(void); 
void ISR_54(void); 
void ISR_55(void); 
void ISR_56(void); 
void ISR_57(void); 
void ISR_58(void);
void ISR_59(void);
void ISR_60(void); 
void ISR_61(void); 
void ISR_62(void); 
void ISR_63(void); 
void ISR_64(void); 
void ISR_65(void); 
void ISR_66(void); 
void ISR_67(void); 
void ISR_68(void);
void ISR_69(void);
void ISR_70(void); 
void ISR_71(void); 
void ISR_72(void); 
void ISR_73(void); 
void ISR_74(void); 
void ISR_75(void); 
void ISR_76(void); 
void ISR_77(void); 
void ISR_78(void);
void ISR_79(void);
void ISR_80(void); 
void ISR_81(void); 
void ISR_82(void); 
void ISR_83(void); 
void ISR_84(void); 
void ISR_85(void); 
void ISR_86(void); 
void ISR_87(void); 
void ISR_88(void);
void ISR_89(void);
void ISR_90(void); 
void ISR_91(void); 
void ISR_92(void); 
void ISR_93(void); 
void ISR_94(void); 
void ISR_95(void); 
void ISR_96(void); 
void ISR_97(void); 
void ISR_98(void);
void ISR_99(void);

IDT_entry IDT[256]; 

IDT_pointer theidtpointer; 

typedef void (*interrupthandlerfunc)(interrupt_stackstate*); 

interrupthandlerfunc InterruptHandlers[256]; 

void Interrupt_Exception_Handler(interrupt_stackstate *stack); 

void SetIDTEntry(int interruptnum,  uint32_t base, uint16_t theselector, uint8_t flags); 

void Interrupt_Handler(interrupt_stackstate *thestack); 

void  load_idt(IDT_pointer ourpointer); 

void IDT_init(void); 

