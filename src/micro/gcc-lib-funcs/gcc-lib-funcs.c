#include <gcc-lib-funcs/gcc-lib-funcs.h>

#include <stdint-gcc.h>

int 	memcmp(const void* ptr1, const void* ptr2, size_t num) { 
	const uint8_t* ptr1_byte = (const uint8_t*)ptr1;
	const uint8_t* ptr2_byte = (const uint8_t*)ptr2;
	
	for (size_t i = 0; i < num; i++) { 
		if (ptr1_byte[i] > ptr2_byte[i]) { 
			return 1;
		} 
		else if (ptr2_byte[i] > ptr1_byte[i]) { 
			return -1; 
		};
	};
	return 0;
}; 

void* 	memset(void* ptr, int value, size_t num) { 
	uint8_t* ptr_byte = (uint8_t*)ptr;

	for (size_t i = 0; i < num; i++) { 
		ptr_byte[i] = (uint8_t)value;
	};
	
	return ptr;
}; 

void* 	memcpy(void* dest, const void* src, size_t num) { 
	uint8_t* dest_byte = (uint8_t*)dest;
	const uint8_t* src_byte = (const uint8_t*)src;
	
	for (size_t i = 0; i < num; i++) { 
		dest_byte[i] = src_byte[i];
	};
	
	return dest;
}; 

void* 	memmove(void* dest, const void* src, size_t num) { 
	uint32_t dest_l = (uint32_t)dest;
	uint32_t src_l = (uint32_t)src;
	
	uint8_t* dest_byte = (uint8_t*)dest;
	const uint8_t* src_byte = (const uint8_t*)src;
	
	if (dest_l < src_l) { 
		memcpy(dest, src, num);
	}
	else { 
		for (size_t i = num; i > 0; i--) { 
			dest_byte[i - 1] = src_byte[i - 1];
		};
	};
	return dest;
};