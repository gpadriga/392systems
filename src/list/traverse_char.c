#include "list.h"
#include "my.h"
#include <stdio.h>

/*
 Prints all the elems as chars separated by a space
*/
void traverse_char(struct s_node* head) {
	while (head) {
		char* ptr = head->elem;
		my_char(*ptr);
		if (head->next) {
			my_char(' ');
			head = head->next;
		}
		else break;
	}
}