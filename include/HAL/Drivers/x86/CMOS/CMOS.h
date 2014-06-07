#include <Utility/Utility.h> 
#include <stdint-gcc.h> 


void CMOS_Disable_NMI(void); 

void CMOS_Enable_NMI(void); 

uint8_t CMOS_GetRegister(int reg); 
