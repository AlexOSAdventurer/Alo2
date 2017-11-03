#include <Utility/Utility.h> 


void panic(const char* msg) { 
	terminal_printf("KERNEL PANIC: %s.", msg);  
	__asm__  __volatile__("cli"); /* Disable interrupts */ 
	for (;;)    ;  
}; 



void itoa(int num, char *thespace, int base) { 
	int currentnumber = abs(num); 
	int charcount = 0; 
	int endcount = 0; 
	char medium[256]; 
	const char *index = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ"; 
	if (currentnumber == 0) { 
		medium[charcount] = '0'; 
		charcount++; 
	}; 
	
	while (currentnumber != 0) { 
		char thechar = index[currentnumber % base]; 
		currentnumber /= base;  
		medium[charcount] = thechar; 
		charcount++; 
	}; 
	
	if ((base == 10) && (num < 0)) { 
		medium[charcount] = '-'; 
	} 
	else { 
		charcount--;
	}; 
	
	
	endcount = charcount + 1; 
	
	for (int i = 0; charcount >= 0; i++) { 
		thespace[i] = medium[charcount]; 
		charcount--; 
	}; 
	
	thespace[endcount] = '\0'; 
}; 	
		
int abs(int thenumber) { 
	if (thenumber < 0) { 
		return -thenumber; 
	}; 
	return thenumber; 
}; 

int ceil_i(int n, int d) { 
	int res = 0;
	if (n % d) { 
		res++;
	}
	res = res + (n / d);
	return res;
}