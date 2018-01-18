#include <Memory/kmalloc_nfree.h>
#include <HAL/Drivers/x86/Paging/paging.h>
#include <Memory/kmalloc.h> 
#include <Utility/Utility.h>

//And yes, I know that this is an utter piece of shit. 


typedef enum {FREE, USED} _kmalloc_type;  // Type of block

struct _kmalloc_header_struct { 
	uint64_t magic;
	uint32_t size; 
	struct _kmalloc_header_struct* prev;
	struct _kmalloc_header_struct* next;
	_kmalloc_type type; 
};

typedef struct _kmalloc_header_struct _kmalloc_header;

_kmalloc_header* blocks = NULL;
_kmalloc_header* blocks_end = NULL;

uint32_t _kmalloc_d_start_addr;
uint32_t _kmalloc_d_max_addr;
uint32_t _kmalloc_d_cur_addr;
uint32_t _kmalloc_d_prev_addr;
uint32_t _kmalloc_d_last_addr;

uint32_t p_n = 0;
uint32_t p_list[KMALLOC_MAX_HEAP / 4096];


//Takes the starting address of an allocation block and returns its header
_kmalloc_header* _kmalloc_get_header(void* ptr) { 
	_kmalloc_header* h = (_kmalloc_header*)((uint32_t)ptr - sizeof(_kmalloc_header));
	if (h->magic != KMALLOC_MAGIC_NUMBER) { 
		panic("Memory header not valid! Possible corruption, or we were given a bad pointer. Either way, not good.");
	};
	return h;
};

//Extends the heap by just one page, and doesn't create any new heap blocks in it. 
void _extend_heap_page(void) {
	//Fetch a new page and place it at the top of the heap. Place the page number in the list we have.
	p_list[p_n] = alloc_page(_kmalloc_d_cur_addr, kernel_dir);
	p_n++;
	//Move up the 
	_kmalloc_d_cur_addr += 4096;
	_kmalloc_d_prev_addr += 4096;
};

//Same as the last, except for heap contraction.
void _contract_heap_page(void) { 
	if (p_n > 0) {
		free_page(_kmalloc_d_prev_addr, kernel_dir, p_list[p_n - 1]);
		p_n--;
		_kmalloc_d_cur_addr -= 4096;
		_kmalloc_d_prev_addr -= 4096;
	};
};

//This extends the heap by at least size. It rounds it to the next page, and it to the mininum expansion amoount if below that. 
void _extend_heap(size_t size) { 
	//Rounds it to the next page boundary. 
	if (size % 4096) { 
		size &= 0xFFFFF000;
		size += 4096;
	};
	//If below the minimum expansion amount. 
	if (size < KMALLOC_MIN_EXP) { 
		size = KMALLOC_MIN_EXP;
	};
	//Allocate each needed page and fill it up with allocation blocks. 
	for (size_t i = 0; i < (size / 4096); i++) { 
		_extend_heap_page();
		//Only as many allocation blocks of the default size that fit. Currently, that is three for every page. This means some allocation blocks cross page boundaries. Keep that in mind. 
		for (uint32_t z = _kmalloc_d_last_addr; (z + KMALLOC_DEF_BLOCK + sizeof(_kmalloc_header)) < _kmalloc_d_cur_addr; z += (KMALLOC_DEF_BLOCK + sizeof(_kmalloc_header))) { 
			//Create the new block header
			_kmalloc_header* n_h = (_kmalloc_header*)z;
			n_h->magic = KMALLOC_MAGIC_NUMBER;
			n_h->size = KMALLOC_DEF_BLOCK;
			n_h->prev = blocks_end;
			n_h->next = NULL;
			n_h->type = FREE;
			//Attach the new block to the end of the block chain if said chain exists. Otherwise, create it. 
			if (blocks_end != NULL) { 
				blocks_end->next = n_h;
			} 
			else { 
				blocks = n_h;
			};
			//Set it as the end of the block chain.
			blocks_end = n_h;
			//Move up the address for the next block. Some redundancy now that I think about it. 
			_kmalloc_d_last_addr += KMALLOC_DEF_BLOCK + sizeof(_kmalloc_header);
		};		
	};
};

//Pops off the top allocation block from the heap, and contracts the heap if it crosses a page boundary while doing so
void _remove_heap_top(void) {
	//Make sure that the heap is not empty
	if (blocks_end != NULL) {
		_kmalloc_header* cur = blocks_end;
		_kmalloc_header* prev = cur->prev;
		//Gets the page number of the current block and the one before
		int page_cur = ((uint32_t)cur) / 4096;
		int page_prev = ((uint32_t)prev) / 4096; 
		//As long as the block before exists, make sure to disconnect it from the block being deleted
		if (prev != NULL) {
			prev->next = NULL;
		} 
		//Otherwise, mark the whole block chain as deleted 
		else { 
			blocks = NULL;
		};
		//Sets the end of the block to prev, which may be NULL
		blocks_end = prev;
		//Set the address for the next block to be placed before the deleted block
		_kmalloc_d_last_addr -= (cur->size + sizeof(_kmalloc_header));
		//If we have crossed a page boundary, then contract the heap by one page
		if (page_prev < page_cur) { 
			_contract_heap_page();
		}
	};
};


void _contract_heap(size_t size) { 
	//Rounds the size down to the next page boundary
	size &= 0xFFFFF000; 
	//Deduct from the heap top
	_kmalloc_d_cur_addr -= size;
	//Keep subtracting from the heap top till it is within the proper boundaries
	while (_kmalloc_d_last_addr > _kmalloc_d_cur_addr) { 
		_remove_heap_top();
	};
};

void _create_heap(void) { 
	//Creates the heap by extending it to the default heap size
	_extend_heap(KMALLOC_MIN_HEAP);
};


//Merge two or more blocks from the start to the end 
void _merge_blocks(_kmalloc_header* start, _kmalloc_header* end) { 
	//Get the address of the very end
	uint32_t end_addr = ((uint32_t)end) + end->size;
	//Get the address of the very start of the block
	uint32_t start_addr = (uint32_t)start + sizeof(_kmalloc_header); 
	//Calculate the size of the whole block
	uint32_t n_size = end_addr - start_addr;
	//Connect the first block to the block that comes immediately after the end, and set it to the new size
	start->size = n_size; 
	start->next = end->next;
	end->next->prev = start;
};


//This splits a block into two new ones, with the original having size size 
void _split_block(_kmalloc_header* block, size_t size) { 
	//Make sure that whatever resulting block is properly aligned
	if (size % KMALLOC_MIN_ALIGN) { 
		size -= (size % KMALLOC_MIN_ALIGN); 
		size += KMALLOC_MIN_ALIGN;
	}
	//Get the new allocation block's address and set it up appropriately
	_kmalloc_header* nblock = (_kmalloc_header*)((uint32_t)block + sizeof(_kmalloc_header) + size);
	nblock->prev = block;
	nblock->next = block->next;
	block->next->prev = nblock;
	block->next = nblock; 
	nblock->size = ((uint32_t)nblock->next) - ((uint32_t)nblock + sizeof(_kmalloc_header));
	block->size = size; 
	nblock->type = FREE;
	nblock->magic = KMALLOC_MAGIC_NUMBER;
};

static uint32_t _find_align_addr(_kmalloc_header* start, _kmalloc_header* end, uint32_t size, uint32_t align) { 
	uint32_t start_addr = (uint32_t)start;
	uint32_t end_addr = (uint32_t)end;
	uint32_t cur_addr = start_addr - (start_addr % align) + align;
	while (cur_addr < end_addr) { 
		uint32_t lsize = cur_addr - start_addr;
		uint32_t rsize = end_addr - cur_addr + end->size;
		if (lsize == sizeof(_kmalloc_header)) { 
			return 1;
		}
		else if ((lsize > sizeof(_kmalloc_header)) && (rsize >= size)) { 
			return cur_addr;
		};
		cur_addr += align;
	};
	return 0;
};

//Allocates a data block of at least size size and returns it
void* _kmalloc(size_t size, uint32_t align, uint32_t* phys) {
	uint32_t res;
	//If no heap exists
	if (blocks == NULL) { 
		return NULL;
	}; 
	_kmalloc_header* cur = blocks; 
	_kmalloc_header* start = blocks; 
	_kmalloc_header* end = blocks;
	uint32_t align_addr;
	uint32_t cur_size;
	//Search for the first available FREE block
	_kmalloc_main: 
	cur_size = 0;
	while (cur->type != FREE) { 
		//Extend the heap if we are out
		if ((cur->next) == NULL) { 
			_extend_heap(size);
		};
		cur = cur->next;
	};
	//See if it forms a long enough chain of memory blocks to work with. Otherwise, go back to the above loop. 
	start = cur;
	while (cur_size < (size * 2)) { 
		cur_size += cur->size + sizeof(_kmalloc_header);
		if (cur->next == NULL) { 
			_extend_heap(size);
		} 
		else if (cur->next->type != FREE) { 
			cur = cur->next;
			goto _kmalloc_main;
		};
		cur = cur->next;
	};
	//Since we went one block too far ahead, correct for it. 
	end = cur->prev;
	_kmalloc_align_check:
	align_addr = _find_align_addr(start, cur, size, align);
	if (align_addr == 0) { 
		if (cur->next == NULL) { 
			_extend_heap(size);
			goto _kmalloc_align_check;
		}
		else { 
			cur = cur->next;
			goto _kmalloc_main;
		};
	} 
	else if (align_addr != 1) { 
		uint32_t dist = align_addr - (uint32_t)start;
		_merge_blocks(start, end);
		_split_block(start, dist - (2 * sizeof(_kmalloc_header)));
		start = start->next;
		end = start;
	};
	
	//If it is more than one block, merge them all.
	if (start != end) { 
		_merge_blocks(start, end);
	}
	//Otherwise, if the block is too big, split it. 
	else if ((start->size - size) > KMALLOC_MAX_DIFF) { 
		_split_block(start, size);
	};
	//Mark the block as used
	start->type = USED;
	//Return the address right after the header. 
	res = (((uint32_t)start) + sizeof(_kmalloc_header));
	if (phys != NULL) { 
		uint32_t p_n = res - _kmalloc_d_start_addr;
		p_n = p_n / 4096;
		p_n--;
		p_n = p_list[p_n];
		*phys = (p_n * 4096) + (res % 4096);
	}
	return (void*)res;
} 


void* kmalloc(size_t size) { 
	return _kmalloc(size, KMALLOC_MIN_ALIGN, NULL);
};

void* kmalloc_a(size_t size, uint32_t align, uint32_t* phys) { 
	return _kmalloc(size, align, phys);
};

//Frees up the block provided to it, and does any heap management and unification it needs to. 
void  kfree(void* ptr) { 
	//Basic initialization. 
	//Implicit magic number check.
	_kmalloc_header* head = _kmalloc_get_header(ptr);
	_kmalloc_header* cur_end = blocks_end;
	_kmalloc_header* cur_end_next;
	//Mark the block as free. 
	head->type = FREE;
	//Merge it with other free blocks 
	while (head->size < KMALLOC_MIN_BLOCK) { 
		_kmalloc_header* tmp;
		_kmalloc_type prev_t = USED;
		_kmalloc_type next_t = USED; 
		//Merge left if possible 
		if ((head->prev != NULL) && (head->prev->type == FREE)) { 
			tmp = head->prev;
			_merge_blocks(head->prev, head);
			head = tmp;
			prev_t = FREE;
		};
		//Merge right 
		if ((head->next != NULL) && (head->next->type == FREE)) {
			_merge_blocks(head, head->next);
			next_t = FREE;
		};		
		//If we are isolated on both sides, stop merging 
		if ((prev_t == USED) && (next_t == USED)) { 
			break; 
		};
	};
	//Lets try to contract 
	while (((_kmalloc_d_cur_addr - _kmalloc_d_start_addr) > KMALLOC_MIN_HEAP) && (cur_end != NULL) && (cur_end->type == FREE)) {
		cur_end_next = cur_end->prev;
		uint32_t next_addr = (uint32_t)(cur_end_next);
		uint32_t end_addr = (uint32_t)(cur_end);
		
		//Checking if we just crossed a page boundary; if so, contract
		if ((next_addr / 4096) > (end_addr / 4096)) { 
			_contract_heap(4096); // It would probably be better just to use a function that contracts one page at a time.
		};
		cur_end = cur_end_next; 
	};
} 

//Just a utility function to get the size of the block given
size_t kmalloc_get_size(void* ptr) { 
	_kmalloc_header* head = _kmalloc_get_header(ptr);
	return (size_t)head->size;
}


//Initializes the heap
void  kmalloc_init(void) { 
	//Sets up all starting variables and creates the heap 
	_kmalloc_d_start_addr = _kmalloc_max_addr + 0x1000;
	_kmalloc_d_max_addr = _kmalloc_d_start_addr + KMALLOC_MAX_HEAP;
	_kmalloc_d_cur_addr = _kmalloc_d_start_addr;
	_kmalloc_d_prev_addr = _kmalloc_d_cur_addr - 4096;
	_kmalloc_d_last_addr = _kmalloc_d_cur_addr;
	_create_heap();
}

