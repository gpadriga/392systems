#include "list.h"
#include <stdio.h>

/*
 Prints all the elems as strings separated by a space in the format
 (NULL <- Elem -> Next elem), ..., (Previous elem <- Elem -> NULL) 
*/
void debug_string(struct s_node* head) {
	//printf("Entering the loop\n");
	while (head != NULL) {
		//printf("I'm in the loop\n");
		char* cptr1 = head->prev ? head->prev->elem : "NULL";
		my_str("(");
		my_str(cptr1);
		my_str(" <- ");

		//printf("I printed out the first thing\n");

		char* cptr2 = head->elem ? head->elem : "NULL";
		my_str(cptr2);
		my_str(" -> ");

		//printf("I printed out the second thing\n");

		char* cptr3 = head->next ? head->next->elem : "NULL";
		my_str(cptr3);
		my_str(")");

		//printf("I printed out the third thing\n");

		head = head->next;
		if (head != NULL) {
			my_str(", ");
		}
	}
	my_char('\n');
}