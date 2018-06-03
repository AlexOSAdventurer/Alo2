#include <Process/process.h>
#include <gcc-lib-funcs/gcc-lib-funcs.h>

#define PROC_MAP_START 0x80000000

static void free_page_process(process_t* proc, int i) { 
        free_page(PROC_MAP_START + (i * PAGING_PAGE_SIZE), proc->dir, proc->pa[i]);
};

Thread_t* spawn_thread(process_t* proc, uint32_t addr) { 
        Thread_t* nt = kmalloc(sizeof(Thread_t));
        memset(nt, 0, sizeof(Thread_t));
        nt->t = create_task();
        LList_add_item(proc->threads, nt);
        task_t* t = nt->t;
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
        proc->threads = LList_create_list();
        create_directory_process(proc, (size / PAGING_PAGE_SIZE) + 1);
        paging_load_dir((page_dir_t*)proc->dir);
        memcpy((void*)(PROC_MAP_START), app, size);
        paging_load_dir(cur);
        spawn_thread(proc, PROC_MAP_START);
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
        uint32_t phys = 0;
        page_dir_t* dir =  paging_create_dir(&phys);
        terminal_printf("%h, %h, %d", phys, (uint32_t)dir, n);
        proc->dir_phys = phys;
        proc->dir = dir;
        //Clear the allocation table to zero.
        memset(proc->pa, 0, 8192);
        //Mirror image it to the kernel directory for everything under 2 GB
        memcpy(dir, kernel_dir, sizeof(page_dir_t) * (PAGING_PAGE_DIRECTORY_LIST_SIZE / 2));
        proc->pn = 0;
        for (size_t i = 0; i < n; i++)  {
                int pn = alloc_page_p(i + PAGING_MEM_MAX / (2 * PAGING_PAGE_SIZE), dir);
                if (pn == -1) {
                        panic("We ran out of memory. Fuck.");
                };
                proc->pa[proc->pn] = pn;
                proc->pn++;
        };

        return dir;
};

void stop_process(process_t* proc) { 
        for (size_t i = 0; i < LList_get_length(proc->threads); i++) {
        		Thread_t* ct = LList_get_item(proc->threads, i);
                remove_task(ct->t);
                kfree(ct->t);
                kfree(ct);
        };
        LList_delete_list(proc->threads);
        free_directory_process(proc);
        kfree(proc);
};
