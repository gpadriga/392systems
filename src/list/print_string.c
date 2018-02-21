#include "list.h"

/*
 Prints the elem of node as a string
*/
void print_string(struct s_node* node) {
	// What do you do if node is NULL?
	if (node == NULL || node->elem == NULL) {
		my_str("NULL\n");
	}
	else {
		// What if node->elem is not a char pointer?
		char* elem = (char*) node->elem;
		my_str(elem);
		my_char('\n');
	}
}