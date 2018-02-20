#include "list.h"

/*
 Returns a pointer to the elem at index n or the last node.
 Parse once.
*/
void* elem_at(struct s_node* head, int n) {
	if (head) {
	    int counter = 0;
		while (head->next && counter < n) { // can increment head itself since not a double ptr
            counter++;
            head = head->next;
		}
		return head->elem; // returns last elem if n too large
	}
	return NULL; // if head is NULL
}