#include "list.h"

/*
 Returns a pointer to the elem at index n or the last node.
 Parse once.
*/
void* elem_at(struct s_node* head, int n) {
	if (head) {
		while (head->next) { // can increment head itself since not a double ptr
			for (int i = 0; i < n; i++) {
				head = head->next;
			}
			return head->elem; // end of for loop
		}
		return head->elem; // returns last elem if n too large
	}
	return NULL; // if head is NULL
}