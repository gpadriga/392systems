#include "list.h"

/*
 Prints the elem of node as an int
*/
void print_int(struct s_node* node) {
	// What do you do if node is NULL?
	if (node == NULL) {
		my_str("NULL\n");
	}
	// What do you do if the element is NULL?
	else if (node->elem == NULL) {
		my_str("NULL\n");
	}
	// What do you do if node->elem is not an int pointer?
	else {
		int* elem = (int*) node->elem;
		my_int(*elem);
		// Should it print a new line?
		my_char('\n');
	}
}