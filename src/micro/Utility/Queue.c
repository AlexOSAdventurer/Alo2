/*
 * Queue.c
 *
 *  Created on: Apr 21, 2018
 *      Author: alex
 */

#include <Utility/Queue.h>

Queue_t* Queue_create_queue() {
	return (Queue_t*)LList_create_list();
}

void Queue_delete_queue(Queue_t* queue) {
	LList_delete_list((LList_t*)queue);
}


void Queue_add_item(Queue_t* queue, void* item) {
	LList_add_item((LList_t*)queue, item);
}


void* Queue_get_next(Queue_t* queue) {
	size_t index = Queue_get_size(queue) - 1;
	void* nitem = LList_get_item((LList_t*)queue, index);
	LList_remove_item((LList_t*)queue, index);
	return nitem;
}

size_t Queue_get_size(Queue_t* queue) {
	return LList_get_length((LList_t*)queue);
}

