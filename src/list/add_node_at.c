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
				if (!cur->next) { // if n is too large
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

int main() {
	struct s_node* a = new_node("windows", NULL, NULL);
	struct s_node* b = new_node("linux", NULL, NULL);
	struct s_node* c = new_node("osx", NULL, NULL);
	struct s_node* d = new_node("ubuntu", NULL, NULL);

	struct s_node* head = a;
	add_node_at(b, &head, 34);
	add_node_at(c, &head, 1);
	add_node_at(d, &head, 3);
	debug_string(head);
	printf("%d\n", count_s_nodes(head));

	void* elem1 = remove_last(&head);
	debug_string(head);
	void* elem2 = remove_last(&head);
	debug_string(head);
	void* elem3 = remove_last(&head);
	debug_string(head);
	void* elem4 = remove_last(&head);
	debug_string(head);
	return 0;
}