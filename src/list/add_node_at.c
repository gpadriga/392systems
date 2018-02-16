#include "list.h"
#include <stdio.h>
#include<stdlib.h>

/*
 Adds a node at index n of a list or at the end of the list if n is 
 too large.
 Parse once
*/
void add_node_at(struct s_node* node, struct s_node** head, int n) {
	if (node && node->elem && head)  { // node and elem both not null
		if (!*head || n <= 0) { // if the head points to an empty list
			add_node(node, head);
		}
		else {
			struct s_node* cur = *head;
			for (int i = 0; i < n; i++) {
				if (cur->next == NULL) {
					cur -> next = node;
					node->prev = cur;
					node->next = NULL;
					return;
				}
				cur = cur->next;
			}
		    cur->prev->next = node;
		    node->next = cur;
		    node->prev = cur->prev;
		    cur->prev = node;
		}
	}
}