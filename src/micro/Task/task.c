#include <stddef.h>
#include <Utility/CLinkedList.h>
#include <gcc-lib-funcs/gcc-lib-funcs.h>
#include <Task/task.h>
#include <HAL/Drivers/x86/Paging/paging.h>
#include <Memory/kmalloc_nfree.h>
#include <Memory/kmalloc.h>
#include <HAL/Interactors/Terminal/Terminal.h>
#include <system-lib/system_lib.h>

Timer* switch_timer = NULL;

volatile CLList_t* task_queue = NULL;

static size_t m_api_number = 0;

static int task_search(void* item, void* data) {
	return item == data;
}

volatile task_t*  __attribute__ ((noinline)) get_current_task() {
	return (volatile task_t*)CLList_stepper_get_current((CLList_t*)task_queue);
}

void __attribute__ ((noinline)) copy_task_state(interrupt_stackstate* s1, interrupt_stackstate* s2) {
	if ((s1 != NULL) && (s2 != NULL)) {
		memcpy(s2, s1, sizeof(interrupt_stackstate));
	};
};

void __attribute__ ((noinline)) save_task_state(interrupt_stackstate* state) {
	if (get_current_task() != NULL) {
		copy_task_state(state, get_current_task()->state);
	}
};

void __attribute__ ((noinline)) setup_task_state(interrupt_stackstate* state) {
	if (get_current_task() != NULL) {
		copy_task_state(get_current_task()->state, state);
		terminal_printf("Addr: %h, %h", (uint32_t)get_current_task()->dir, (uint32_t)get_current_task());
		paging_load_dir((page_dir_t*)get_current_task()->dir);
	};
}

void switch_task_handler(interrupt_stackstate* state) { 
	terminal_putstring("YIELDING!\n");
	save_task_state(state);
	switch_task();
	setup_task_state(state);
};

void  __attribute__ ((noinline)) switch_task(void) {
	CLList_stepper_next((CLList_t*)task_queue);
}; 

void add_task(task_t* t) { 
	CLList_add_item((CLList_t*)task_queue, t);
}; 

void remove_task(task_t* t) { 
	if (t == get_current_task())  {
		switch_task();
	};
	int index = (size_t)CLList_search_list((CLList_t*)task_queue, task_search, t);
	if (index > 0) {
		CLList_remove_item((CLList_t*)task_queue, (size_t)index);
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
	t1->dir = kernel_dir;
	add_task(t1);
};

static void create_task_queue() {
	task_queue = CLList_create_list();
}

void task_init(void) {
	create_task_queue();
	create_root_task();
	system_lib_handlers[m_api_number] = switch_task_handler;
	switch_timer = kmalloc_nfree(sizeof(Timer), 0);
	memset((void*)switch_timer, 0, sizeof(Timer));
	switch_timer->func = switch_task_handler;
	switch_timer->limit = 200;
	Timer_Register_Timer(switch_timer);
};

