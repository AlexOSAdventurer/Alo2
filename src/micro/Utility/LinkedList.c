#include <stddef.h>
#include <Memory/kmalloc.h>
#include <Utility/LinkedList.h>
#include <gcc-lib-funcs/gcc-lib-funcs.h>


static LList_t* LList_clear_item(LList_t* l) {
	return memset(l, 0, sizeof(LList_t));
}

static void LList_connect_nodes(LList_t* n, LList_t* prev, LList_t* next) {
	n->prev = prev;
	n->next = next;
	if (prev != NULL) {
		prev->next = n;
	};
	if (next != NULL) {
		next->prev = n;
	};
}

static void LList_init_root(LList_t* l) {
	LList_connect_nodes(l, l, l);
	l->present = 0;
}

static LList_t* LList_create_item() {
	LList_t* res = LList_clear_item((LList_t*)kmalloc(sizeof(LList_t)));
	res->present = 1;
	return res;
}

LList_t* LList_create_list() {
	LList_t* list = LList_create_item();
	LList_init_root(list);
	return list;
}

void LList_delete_list(LList_t* l) {
	for (size_t i = 0; i < LList_get_length(l); i++) {
		LList_remove_item(l, l);
	}
}

void LList_add_item(LList_t* list, void* i) {
	LList_t* ni;
	LList_t* next = list->next;
	if (!list->present) {
		ni = list;
		ni->present = 1;
	}
	else {
		ni = LList_create_item();
	}
	LList_connect_nodes(ni, list, next);
	ni->item = i;
}

void LList_remove_item(LList_t* l, LList_t* i) {
	if (l == i) {
		LList_t* next = LList_get_next(l);
		void* item1 = LList_get_item(l);
		void* item2 = LList_get_item(next);
		l->item = item2;
		next->item = item1;
	}
	if ((i->next == i) || (i->prev == i)) {
		LList_init_root(i);
	}
	else {
		LList_connect_nodes(i->prev, i->prev->prev, i->next);
		kfree(i);
	};
}

LList_t* LList_get_prev(LList_t* i) {
	return i->prev;
}

LList_t* LList_get_next(LList_t* i) {
	return i->next;
}

void* LList_get_item(LList_t* i) {
	return i->item;
}

LList_t* LList_get_n(LList_t* list, int l) {
	LList_t* ce = list;
	for (int n = 1; n < l; n++, ce = ce->next);
	return ce;
}

size_t LList_get_length(LList_t* list) {
	LList_t* ce = list;
	if (!list->present) {
		return 0;
	}
	else {
		size_t n;
		for (n = 1; ce->next != list; n++, ce = ce->next);
		return n;
	};
}

LList_t* LList_search_list(LList_t* list, int(*f)(void*, void*), void* data) {
	LList_t* ce = list;
	for (size_t n = 1; n <= LList_get_length(list); n++, ce = ce->next) {
		void* item = ce->item;
		if (f(item, data)) {
			return ce;
		}
	}
	return NULL;
}


