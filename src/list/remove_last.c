#include "list.h"

/*
 Removes the last node from the list.
 Parse Once.
*/
void* remove_last(struct s_node** head) {
	if (head && *head) {
		struct s_node* cur = *head;
		while (cur->next){
			cur = cur->next;
		}
		if (cur->prev) {
			cur->prev->next = NULL;
			cur->prev = NULL;
		}
		void * temp = cur->elem;
		free(cur);
		return temp;
	}
	return NULL;
}