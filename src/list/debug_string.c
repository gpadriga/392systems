#include "list.h"

/*
 Prints all the elems as strings separated by a space in the format
 (NULL <- Elem -> Next elem), ..., (Previous elem <- Elem -> NULL) 
*/
void debug_string(struct s_node* head) {
	while (head != NULL) {
		char* cptr1 = head->prev ? head->prev->elem : "NULL";
		my_str("(");
		my_str(cptr1);
		my_str(" <- ");
		char* cptr2 = head->elem ? head->elem : "NULL";
		my_str(cptr2);
		my_str(" -> ");
		char* cptr3 = head->next ? head->next->elem : "NULL";
		my_str(cptr3);
		my_str(")");
		head = head->next;
		if (head != NULL) {
			my_str(", ");
		}
	}
	my_char('\n');
}