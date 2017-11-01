#ifndef PAGE_ALLOC_H
#define PAGE_ALLOC_H




int alloc_page(uint32_t addr, page_dir_t* dir);
void free_page(uint32_t addr, page_dir_t* dir, uint32_t p);
void page_alloc_init(uint32_t max_page, uint32_t max_kern_page);

#endif