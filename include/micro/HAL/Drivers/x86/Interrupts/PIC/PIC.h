#define PIC1 0x20 
#define PIC2 0xA0 
#define PIC1_COMMANDPORT PIC1 
#define PIC1_DATAPORT (PIC1 + 1) 
#define PIC2_COMMANDPORT PIC2 
#define PIC2_DATAPORT (PIC2 + 1) 
#define PIC_EOI 0x20 
#define PIC_READ_IRR 0x0A 
#define PIC_READ_ISR  0x0B 
#define PIC_DISABLECODE 0xFF

#include <Utility/Utility.h>

uint16_t PIC_get_irq_register(int ocw3); 

uint16_t PIC_get_irr(void);  

uint16_t PIC_get_isr(void); 

void PIC_SetMask(int irqnumber); 

void PIC_ClearMask(int irqnumber); 

void PIC_remap(int firstoffset, int secondoffset); 

void PIC_SendEOI(int irqnumber); 

void PIC_Disable(void); 

void PIC_init(void); 



