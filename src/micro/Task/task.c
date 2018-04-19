#include <stddef.h>
#include <Utility/LinkedList.h>
#include <gcc-lib-funcs/gcc-lib-funcs.h>
#include <Task/task.h>
#include <HAL/Drivers/x86/Paging/paging.h>
#include <Memory/kmalloc_nfree.h>
#include <Memory/kmalloc.h>
#include <HAL/Interactors/Terminal/Terminal.h>
#include <system-lib/system_lib.h>

Timer* switch_timer = NULL;

volatile LList_t* task_queue = NULL;
volatile LList_t* task_current = NULL;

static size_t m_api_number = 0;

static int task_search(void* item, void* data) {
	return item == data;
}

static task_t* get_current_task() {
	return (task_t*)LList_get_item((LList_t*)task_current);
}

void copy_task_state(interrupt_stackstate* s1, interrupt_stackstate* s2) {
	if ((s1 != NULL) && (s2 != NULL)) {
		memcpy(s2, s1, sizeof(interrupt_stackstate));
	};
};

static void save_task_state(interrupt_stackstate* state) { 
	if (task_current != NULL) {
		copy_task_state(state, get_current_task()->state);
	}
};

void setup_task_state(interrupt_stackstate* state) {
	if (task_current != NULL) {
		copy_task_state(get_current_task()->state, state);
		terminal_printf("Addr: %h", (uint32_t)get_current_task()->dir);
		paging_load_dir((page_dir_t*)get_current_task()->dir);
	};
}

void switch_task_handler(interrupt_stackstate* state) { 
	terminal_putstring("YIELDING!\n");
	save_task_state(state);
	switch_task();
	setup_task_state(state);
};

void switch_task(void) { 
	task_current = (volatile LList_t*)LList_get_next((LList_t*)task_current);
}; 

void add_task(task_t* t) { 
	LList_add_item((LList_t*)task_queue, t);
}; 

void remove_task(task_t* t) { 
	if (t == get_current_task())  {
		switch_task();
	};
	LList_remove_item((LList_t*)task_queue, LList_search_list((LList_t*)task_queue, task_search, t));
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
	task_queue = LList_create_list();
	task_current = task_queue;
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

