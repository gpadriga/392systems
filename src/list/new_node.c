#include "list.h"

/*
 Allocates and returns a new node with the given pointers. You may
 create nodes with NULLs.
*/
struct s_node* new_node(void* elem, struct s_node* next, struct s_node* previous) {
	struct s_node* node = malloc(sizeof(struct s_node*));
	node->elem = elem;
	node->next = next;
	node->prev = previous;
	return node;
}