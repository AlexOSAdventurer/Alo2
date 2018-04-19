#ifndef LLIST_H
#define LLIST_H

#include <stddef.h>

typedef struct LList {
	struct LList* prev;
	struct LList* next;
	void* item;
	int present;
} LList_t;


LList_t* LList_create_list();
void LList_add_item(LList_t* list, void* i);
void LList_remove_item(LList_t* list, LList_t* i);
LList_t* LList_get_prev(LList_t* i);
LList_t* LList_get_next(LList_t* i);
void* LList_get_item(LList_t* i);
LList_t* LList_get_n(LList_t* list, int l);
size_t LList_get_length(LList_t* list);
LList_t* LList_search_list(LList_t* list, int(*f)(void*, void*), void* data);

#endif
