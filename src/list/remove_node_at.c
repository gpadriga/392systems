#include "list.h"

/*
 Removes the node at index n or the last node.
 Parse once
*/
void* remove_node_at(struct s_node** head, int n) {
	// If head or *head is null, return null?
	if (head == NULL || *head == NULL) {
		return NULL;
	}
	// if n < 0, set n = 0
	if (n <= 0) {
		return remove_node(head);
	}
	struct s_node* cur = *head;
	// traverse to the node you want to remove
	while (n > 0 && cur->next != NULL) {
		cur = cur->next;
		n--;
	}
	// remove the node
	return remove_node(&cur);
}