#include <stddef.h>
#include <gcc-lib-funcs/gcc-lib-funcs.h>
#include <Task/task.h>
#include <HAL/Drivers/x86/Paging/paging.h>
#include <Memory/kmalloc_nfree.h>
#include <Memory/kmalloc.h>
#include <HAL/Interactors/Terminal/Terminal.h>
#include <system-lib/system_lib.h>

Timer* switch_timer = NULL;

task_t* task_queue = NULL;
task_t* task_current = NULL;

static size_t m_api_number = 0;

uint32_t task_lowest_pid = 0;

static void copy_task_state(interrupt_stackstate* s1, interrupt_stackstate* s2) { 
	if ((s1 != NULL) && (s2 != NULL)) { 
		memcpy(s2, s1, sizeof(interrupt_stackstate));
	};
};

static void save_task_state(interrupt_stackstate* state) { 
	if (task_current != NULL) { 
		copy_task_state(state, task_current->state);
	}
};

static void setup_task_state(interrupt_stackstate* state) { 
	if (task_current != NULL) { 
		copy_task_state(task_current->state, state);
		//terminal_printf("Addr: %h", (uint32_t)task_current->dir);
		paging_load_dir((page_dir_t*)task_current->dir);
	};
}

void switch_task_handler(interrupt_stackstate* state) { 
	terminal_putstring("YIELDING!\n");
	save_task_state(state);
	switch_task();
	setup_task_state(state);
};

void switch_task(void) { 
	if (task_current != NULL)  {
		task_current = task_current->next;
	};
}; 

void add_task(task_t* t) { 
	if (task_queue != NULL) {
		t->prev = task_queue->prev;
		t->next = task_queue->next;
		t->prev->next = t;
		t->next->prev = t;
	}
	else { 
		task_current = t;
		t->prev = t;
		t->next = t;
	};
	task_queue = t;
}; 


void remove_task(task_t* t) { 
	if (t == task_current)  {
		switch_task();
	};
	if (t->prev != NULL) {
		t->prev->next = t->next;
	};
	
	if (t->next != NULL)  {
		t->next->prev = t->prev;
	};
};

task_t* create_task() { 
	task_t* t = kmalloc(sizeof(task_t));
	memset(t, 0, sizeof(task_t));
	t->state = kmalloc(sizeof(interrupt_stackstate));
	memset(t->state, 0, sizeof(interrupt_stackstate));
	return t;
};

static void create_root_task() { 
	task_t* t1 = create_task();
	//task_t* t2 = create_task();
	t1->dir = kernel_dir;
	//t2->dir = kernel_dir;
	
	add_task(t1);
};

void task_init(void) {
	create_root_task();
	system_lib_handlers[m_api_number] = switch_task_handler;
	switch_timer = kmalloc_nfree(sizeof(Timer), 0);
	memset((void*)switch_timer, 0, sizeof(Timer));
	switch_timer->func = switch_task_handler;
	switch_timer->limit = 200;
	Timer_Register_Timer(switch_timer);
};


