#include "list.h"
#include <stdio.h>

/*
 Prints all the elems as strings separated by a space in the format
 (NULL <- Elem -> Next elem), ..., (Previous elem <- Elem -> NULL) 
*/
void debug_string(struct s_node* head) {
	while (head->next != NULL) {
		char* cptr = node->prev->elem;
		printf("%s", cptr);
		printf("%s", " <- ");
		char* cptr = node->elem;
		printf("%s", cptr);
		printf("%s", " -> ");
		char* cptr = node->next->elem;
		printf("%s", cptr);
		head = head->next;
	}
}