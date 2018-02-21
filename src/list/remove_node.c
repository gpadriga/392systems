#include "list.h"

/* 
 Removes the given node from the list. Returns elem and frees the 
 node from memory.
 DOES NOT PARSE.
*/
void* remove_node(struct s_node** node) {
	// * Should you set node-> prev and node-> elem to null? *
	// * What does removing a single node look like? *

	// if node is null or *node is null, return null
	if (node == NULL || *node == NULL) {
		return NULL;
	}
	// if node->prev is not null, update node->prev->next
	if ((*node)->prev != NULL) {
		(*node)->prev->next = (*node)->next;
	}
	// if node->next is not null, update node->next->prev
	if ((*node)->next != NULL) {
		(*node)->next->prev = (*node)->prev;
	}
	// grab elem
	void* elem = (*node)->elem;
	// free node
	free(*node);
	// return elem
	return elem;
}