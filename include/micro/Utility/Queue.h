/*
 * Queue
 *
 *  Created on: Apr 21, 2018
 *      Author: alex
 */

#ifndef QUEUE_H
#define QUEUE_H

#include <stddef.h>
#include <Utility/LinkedList.h>


typedef LList_t Queue_t;

Queue_t* Queue_create_queue();
void Queue_delete_queue(Queue_t* queue);
void Queue_add_item(Queue_t* queue, void* item);
void* Queue_get_next(Queue_t* queue);
size_t Queue_get_size(Queue_t* queue);

#endif
