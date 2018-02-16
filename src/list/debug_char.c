#include "list.h"
#include <stdio.h>

/*
 Prints all the elems as chars separated by a space in the format
 (NULL <- Elem -> Next elem), ..., (Previous elem <- Elem -> NULL) 
*/
void debug_char(struct s_node* head) {
	while (head->next != NULL) {
		char cptr = head->p rev->elem;
		my_char(cptr);
		my_str(" <- ");
		char cptr2 = head->elem;
		printf("%s", cptr2);
		my_str(" -> ");
		char cptr3 = head->next->elem;
		my_char(cptr3);
		head = head->next;
	}
}