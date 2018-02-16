#include "list.h"

/*
 Returns the value the length of the list
 Parse Once.
*/
int count_s_nodes(struct s_node* head) {
	int count = 0;
	while (head != NULL) {
		count++;
		head = head->next;
	}
	return count;
}