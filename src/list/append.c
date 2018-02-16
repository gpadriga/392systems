#include "list.h"

/*
 Adds a node to the end of a list. DO NOT add a NULL pointer or
 a node with a NULL elem.
 Parse once
*/
void append(struct s_node* node, struct s_node** head) {
	if (node && node->elem && head)  { // node and elem both not null
		if (!*head) {
			add_node(node, head);
		}
		struct s_node* cur = *head;
		while(cur->next) {
			cur = cur->next;
			if (!cur->next) {
				break;
			}
		}
		cur -> next = node;
		node->prev = cur;
		// set node->next to null?
		return;
	}
}