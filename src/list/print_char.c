#include "list.h"

/*
 Prints the elem of node as a char
*/
void print_char(struct s_node* node) {
	// What do you do if node is NULL?
	if (node == NULL) {
		my_str("NULL\n");
	}
	// What do you do if the element is NULL?
	else if (node->elem == NULL) {
		my_str("NULL\n");
	}
	else {
		// What if node->elem is not a char pointer?
		char* elem = (char*) node->elem;
		my_char(*elem);
		my_char('\n');
	}
}