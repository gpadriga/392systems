#include "list.h"

/*
 Returns a pointer to the node at index n or the last node.
 Parse once
*/
struct s_node* node_at(struct s_node* head, int n) {
	if (head) {
		while (head->next) { // can increment head itself since not a double ptr
			for (int i = 0; i < n; i++) {
				head = head->next;
			}
			return head;
		}
		return head; // returns last elem if n too large
	}
	return NULL;
}