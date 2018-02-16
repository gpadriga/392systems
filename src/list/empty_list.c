#include "list.h"

/*
 Frees all the nodes in the list.
 CHALLENGE: Write in two lines (allowed to use other methods in 
 this assignment)
*/
void empty_list(struct s_node** head) {
	while (head && *head) {
			remove_last(head);
	}
}