#include "list.h"
#include "my.h"

void debug_int(struct s_node* head) {
	while (head != NULL) {
		//printf("I'm in the loop\n");
		my_str("(");
		if (head->prev && head->prev->elem) {
			int* iptr1 = head->prev->elem;
			my_int(*iptr1);
		}
		else {
			my_str("NULL");
		}
		my_str(" <- ");

		//printf("I printed out the first thing\n");

		if (head->elem) {
			int* iptr2 = head->elem;
			my_int(*iptr2);
		}
		else {
			my_str("NULL");
		}
		my_str(" -> ");

		//printf("I printed out the second thing\n");

		if (head->next && head->next->elem) {
			int* iptr3 = head->next->elem;
			my_int(*iptr3);
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