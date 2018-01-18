#include <Process/process.h>
#include <gcc-lib-funcs/gcc-lib-funcs.h>

static void free_page_process(process_t* proc, int i) { 
	free_page(0x80000000 + (i * 4096), proc->dir, proc->pa[i]);
};

Thread_t* spawn_thread(process_t* proc, uint32_t addr) { 
	Thread_t* nt = kmalloc(sizeof(Thread_t));
	memset(nt, 0, sizeof(Thread_t));
	nt->t = create_task();
	if (proc->threads == NULL) { 
		proc->threads = nt;
	}
	else { 
		if (proc->threads->next) { 
			nt->next = proc->threads->next;
			nt->next->prev = nt;
		}
		nt->prev = proc->threads;
		proc->threads->next = nt;
	};
	task_t* t = proc->threads->t;
	interrupt_stackstate* st = t->state;
	st->eip = addr;
	st->eflags = 0x101202;
	st->gs = 0x10;
	st->fs = 0x10;
	st->es = 0x10;
	st->ds = 0x10;
	st->cs = 0x08;
	t->dir = proc->dir;
	t->dir_phys = proc->dir_phys;
	add_task(t);
	return nt;
}

process_t* spawn_process(void* app, size_t size) { 
	page_dir_t* cur = paging_cur_dir;
	process_t* proc = kmalloc(sizeof(process_t));
	create_directory_process(proc, (size / 4096) + 1);
	paging_load_dir((page_dir_t*)proc->dir);
	memcpy((void*)(0x80000000), app, size);
	paging_load_dir(cur); 
    spawn_thread(proc, 0x80000000);
	return proc;
};

void free_directory_process(process_t* proc) { 
	for (int i = 0; i < proc->pn; i++) { 
		free_page_process(proc, i);
	};
	kfree(proc->dir);
};

//Creates a directory for a process. n is the number of pages to be tacked at the 2 GB line. 
//This directory should basically be ready to go and launch a process. 
//You just need to actually load what you need at the 2 GB mark ;) 
page_dir_t* create_directory_process(process_t* proc, size_t n) { 
	uint32_t phys;
	page_dir_t* dir = kmalloc_a(sizeof(page_dir_t) * 1024, 4096, &phys);
	terminal_printf("%h, %h, %d", phys, (uint32_t)dir, n);
	proc->dir_phys = phys;
	proc->dir = dir;
	//Clear the new directory and the allocation table to zero. 
	memset(dir, 0, sizeof(page_dir_t) * 1024);
	memset(proc->pa, 0, 8192);
	//Mirror image it to the kernel directory for everything under 2 GB 
	memcpy(dir, kernel_dir, sizeof(page_dir_t) * 512);
	proc->pn = 0;
	for (size_t i = 524288; i < (n + 524288); i++)  { 
		int pn = alloc_page_p(i, dir);
		if (pn == -1) { 
			panic("We ran out of memory. Fuck.");
		};
		proc->pa[proc->pn] = pn;
		proc->pn++;
	};
	
	return dir;
};

void stop_process(process_t* proc) { 
	for (Thread_t* i = proc->threads; i->next != NULL; i = i->next) { 
		remove_task(i->t);
		kfree(i->t);
	};
	free_directory_process(proc);
	kfree(proc);
};


