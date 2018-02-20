#include "list.h"

/*
 Returns a pointer to the node at index n or the last node.
 Parse once
*/
struct s_node* node_at(struct s_node* head, int n) {
	if (head) {
	    int counter = 0;
		while (head->next && count < n) { // can increment head itself since not a double ptr
			counter++;
			head = head->next;
		}
		return head; // returns last elem if n too large
	}
	return NULL;
}