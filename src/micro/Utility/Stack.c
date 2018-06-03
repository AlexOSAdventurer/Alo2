/*
 * Stack.c
 *
 *  Created on: Apr 20, 2018
 *      Author: alex
 */


#include <Utility/Stack.h>


Stack_t* Stack_create_stack(void) {
	return (Stack_t*)LList_create_list();
}

void Stack_delete_stack(Stack_t* stack) {
	LList_delete_list((LList_t*)stack);
}

void* Stack_pop(Stack_t* stack) {
	void* res = LList_get_item((LList_t*)stack, 0);
	LList_remove_item((LList_t*)stack, 0);
	return res;
}

void Stack_push(Stack_t* stack, void* item) {
	LList_add_item((LList_t*)stack, item);
}

size_t Stack_get_size(Stack_t* stack) {
	return LList_get_length((LList_t*)stack);
}
