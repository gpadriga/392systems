#include "list.h"

/*
 Returns a pointer to the elem at index n or the last node.
 Parse once.
*/
void* elem_at(struct s_node* head, int n) {
	if (head) {
		return (node_at(head, n))->elem;
	}
	return NULL;
}