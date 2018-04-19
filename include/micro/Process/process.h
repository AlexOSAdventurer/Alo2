#ifndef PROCESS_H
#define PROCESS_H

#include <stdint-gcc.h>
#include <stddef.h>
#include <Task/task.h>
#include <HAL/Drivers/x86/Paging/paging.h>
#include <Utility/Utility.h>
#include <Utility/LinkedList.h>
#include <Memory/kmalloc.h>


typedef struct Thread { 
	//struct Thread* prev;
	//struct Thread* next;
	task_t* t;
} Thread_t;

typedef struct { 
	LList_t* threads;
	page_dir_t* dir;
	uint32_t dir_phys;
	int pn;
	int pa[2048];
} process_t;



process_t* proc_list;



page_dir_t* create_directory_process(process_t* proc, size_t n);
void free_directory_process(process_t* proc);
Thread_t* spawn_thread(process_t* proc, uint32_t addr);
process_t* spawn_process(void* app, size_t size);
void stop_process(process_t* proc);


#endif
