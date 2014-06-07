#pragma once 

#include <HAL/Drivers/x86/CMOS/CMOS.h> 

typedef struct { 
	const char* month; 
	const char* weekday; 
	int seconds; 
	int minute; 
	int hour; 
	int year; 
	int dayinmonth; 
} DateAndTime; 

const char* GetMonth(void); 

const char* GetWeekDay(void); 

int GetDayInMonth(void); 

int GetYear(void); 

int GetHour(void); 

int GetMinute(void); 

int GetSecond(void); 

void GetDateAndTime(DateAndTime *thepointer); 
