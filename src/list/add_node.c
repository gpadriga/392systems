#include "list.h"
#include <stdio.h>
#include<stdlib.h>

/*
 Inserts a node at the start of the list. DO NOT add a NULL pointer or
 a node with a NULL elem.
 DOES NOT PARSE
*/
void add_node(struct s_node* node, struct s_node** head) {
	if (node && node->elem && head)  { // node and elem both not null
		if (!*head) { // if the head points to an empty list
			*head = node;
			node->prev = NULL;
		}
		else {
			(**head).prev = node;
			node->next = *head;
			node->prev = NULL;
			*head = node;
		}
	}
}

// int main() {
// 	struct s_node* first = new_node("im first", NULL, NULL);
// 	struct s_node* head = new_node("im the head", NULL, NULL);
// 	add_node(first, &head);
// 	debug_string(first);
// 	return 0;
// }