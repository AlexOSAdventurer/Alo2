/*
 * CLinkedList.h
 *
 *  Created on: Apr 20, 2018
 *      Author: alex
 */

#ifndef CLINKEDLIST_H
#define CLINKEDLIST_H

#include <Memory/kmalloc.h>
#include <gcc-lib-funcs/gcc-lib-funcs.h>
#include <Utility/LinkedList.h>

typedef struct CLList {
	LList_t* list;
	size_t position;
} CLList_t;


CLList_t* CLList_create_list();
void CLList_delete_list(CLList_t* list);
void CLList_add_item(CLList_t* list, void* item);
void CLList_remove_item(CLList_t* list, size_t index);
void* CLList_get_item(CLList_t* list, size_t index);
size_t CLList_get_length(CLList_t* list);
int CLList_search_list(CLList_t* list, int(*f)(void*, void*), void* data);
void CLList_stepper_next(CLList_t* list);
void* CLList_stepper_get_current(CLList_t* list);
void CLList_stepper_reset(CLList_t* list);


#endif
