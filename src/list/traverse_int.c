#include "list.h"

/*
 Prints all the elems as ints separated by a space
*/
void traverse_int(struct s_node* head) {
	while (head) {
		int* ptr = head->elem;
		my_int(*ptr);
		if (head->next) {
			my_char(' ');
			head = head->next;
		}
		else break;
	}
}