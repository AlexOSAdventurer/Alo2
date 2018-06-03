/*
 * CLinkedList.c
 *
 *  Created on: Apr 20, 2018
 *      Author: alex
 */


#include <Utility/CLinkedList.h>

CLList_t* CLList_create_list() {
	CLList_t* list = (CLList_t*)memset(kmalloc(sizeof(CLList_t)), (int)NULL, sizeof(CLList_t));
	list->list = LList_create_list();
	return list;
}

void CLList_delete_list(CLList_t* list) {
	LList_delete_list(list->list);
	kfree(list);
}

void CLList_add_item(CLList_t* list, void* item) {
	LList_add_item_to_end(list->list, item);
}

void CLList_remove_item(CLList_t* list, size_t index) {
	LList_remove_item(list->list, index);
	if (index < list->position) {
		list->position = list->position - 1;
	};
}

void* CLList_get_item(CLList_t* list, size_t index) {
	return LList_get_item(list->list, index);
}

size_t CLList_get_length(CLList_t* list) {
	return LList_get_length(list->list);
};

int CLList_search_list(CLList_t* list, int(*f)(void*, void*), void* data) {
	return LList_search_list(list->list, f, data);
};

void CLList_stepper_next(CLList_t* list) {
	list->position = list->position + 1;
	if (list->position >= LList_get_length(list->list)) {
		CLList_stepper_reset(list);
	}
}

void* CLList_stepper_get_current(CLList_t* list) {
	return LList_get_item(list->list, list->position);
}

void CLList_stepper_reset(CLList_t* list) {
	list->position = 0;
}
