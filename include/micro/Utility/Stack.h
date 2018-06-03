/*
 * Stack.h
 *
 *  Created on: Apr 20, 2018
 *      Author: alex
 */

#ifndef STACK_H
#define STACK_H

#include <Utility/LinkedList.h>
#include <stddef.h>

typedef LList_t Stack_t;

Stack_t* Stack_create_stack(void);
void Stack_delete_stack(Stack_t* stack);
void* Stack_pop(Stack_t* stack);
void Stack_push(Stack_t* stack, void* item);
size_t Stack_get_size(Stack_t* stack);




#endif
