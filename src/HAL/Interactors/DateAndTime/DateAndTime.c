#include <HAL/Interactors/DateAndTime/DateAndTime.h> 

static const char* months[] = { 
	"January", 
	"February", 
	"March", 
	"April", 
	"May", 
	"June", 
	"July", 
	"August", 
	"September", 
	"October", 
	"November", 
	"December" 
}; 

static const char* weekdays[] = { 
	"Sunday", 
	"Monday", 
	"Tuesday", 
	"Wednesday", 
	"Thursday", 
	"Friday", 
	"Saturday" 
}; 

const char* GetMonth(void) { 
	return months[(CMOS_GetRegister(8) - 1)]; 
}; 

const char* GetWeekDay(void) { 
	return weekdays[(CMOS_GetRegister(6) - 1)]; 
}; 

int GetDayInMonth(void) { 
	return (int)(CMOS_GetRegister(7)); 
}; 

int GetYear(void) { 
	return (int)(((uint16_t)CMOS_GetRegister(9) << 8) | ((uint16_t)CMOS_GetRegister(10))); 
}; 


int GetHour(void) { 
	return (int)(CMOS_GetRegister(4)); 
}; 


int GetMinute(void) { 
	return (int)(CMOS_GetRegister(2)); 
}; 


int GetSecond(void) { 
	return (int)(CMOS_GetRegister(0)); 
}; 


void GetDateAndTime(DateAndTime *thepointer) { 
	thepointer->month = GetMonth(); 
	thepointer->weekday = GetWeekDay(); 
	thepointer->seconds = GetSecond(); 
	thepointer->minute = GetMinute(); 
	thepointer->hour = GetHour(); 
	thepointer->year = GetYear(); 
	thepointer->dayinmonth = GetDayInMonth(); 
}; 