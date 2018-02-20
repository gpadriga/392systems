#include "list.h"
#include "my.h"

/*
 Prints all the elems as strings separated by a space
*/
void traverse_int(struct s_node* head) {
	while (head) {
		char* ptr = head->elem;
		my_str(*ptr);
		if (head->next) {
			my_char(' ');
			head = head->next;
		}
	}
}