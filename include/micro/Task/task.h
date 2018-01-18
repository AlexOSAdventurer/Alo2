#ifndef TASK_H
#define TASK_H

#include <HAL/Drivers/x86/Paging/paging.h>
#include <HAL/Interactors/Timer/Timer.h>
#include <stdint-gcc.h>
#include <stddef.h>

/*
typedef struct registers { 
	uint32_t ds; 
	uint32_t edi, esi, ebp, esp, ebx, edx, ecx, eax; 
	uint32_t eip, cs, eflags, ss; 
} registers_t; 
*/

struct task { 
	uint32_t pid;
	uint32_t level;
	interrupt_stackstate* state;
	page_dir_t* dir;
	uint32_t dir_phys;
	struct task* prev;
	struct task* next;
};

typedef struct task task_t;


void switch_task(void);
void add_task(task_t* t);
void remove_task(task_t* t);
task_t* create_task(void);
void task_init(void);

#endif