#include "list.h"
#include <stdio.h>

/*
 Prints all the elems as strings separated by a space in the format
 (NULL <- Elem -> Next elem), ..., (Previous elem <- Elem -> NULL) 
*/
void debug_string(struct s_node* head) {
	while (head->next != NULL) {
		char* cptr = head->p rev->elem;
		printf("%s", cptr);
		printf("%s", " <- ");
		char* cptr2 = head->elem;
		printf("%s", cptr2);
		printf("%s", " -> ");
		char* cptr3 = head->next->elem;
		printf("%s", cptr3);
		head = head->next;
	}
} 