#include "list.h"

/* 
 Creates a new node with elem and adds it to head. DO NOT add a NULL 
 elem.
 DOES NOT PARSE
*/
void add_elem(void* elem, struct s_node** head) {
	if (elem) {
		struct s_node* n = new_node(elem, NULL, NULL);
		add_node(n, head);
	}
}