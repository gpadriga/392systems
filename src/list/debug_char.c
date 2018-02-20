#include "list.h"
#include "my.h"

void debug_char(struct s_node* head) {
	while (head != NULL) {
		//printf("I'm in the loop\n");
		my_str("(");
		if (head->prev && head->prev->elem) {
			char* cptr1 = head->prev->elem;
			my_char(*cptr1);
		}
		else {
			my_str("NULL");
		}
		my_str(" <- ");

		//printf("I printed out the first thing\n");

		if (head->elem) {
			char* cptr2 = head->elem;
			my_char(*cptr2);
		}
		else {
			my_str("NULL");
		}
		my_str(" -> ");

		//printf("I printed out the second thing\n");

		if (head->next && head->next->elem) {
			char* cptr3 = head->next->elem;
			my_char(*cptr3);
		}
		else {
			my_str("NULL");
		}
		my_str(")");

		//printf("I printed out the third thing\n");

		head = head->next;
		if (head != NULL) {
			my_str(", ");
		}
	}
	my_char('\n');	
}