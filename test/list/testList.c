#include "list.h"
#include <stdio.h>

void test_print_int() {
	int x = 4;
	int* xp = &x;
	struct s_node* node = new_node(xp, NULL, NULL);
	print_int(node);
	print_int(NULL);
	struct s_node* node2 = new_node(NULL, NULL, NULL);
	print_int(node2);
}

void test_print_char() {
	char c = 'a';
	struct s_node* node3 = new_node(&c, NULL, NULL);
	print_char(node3);
	print_char(NULL);
	print_int(node3);

	my_int('a');
	my_char('\n');
}

void test_print_string() {
	struct s_node* node4 = new_node("iron fist", NULL, NULL);
	print_string(node4);
	print_string(NULL);
}

void test_add_node() {
	struct s_node* first = new_node("im first", NULL, NULL);
	struct s_node* head = new_node("im the head", NULL, NULL);
	add_node(first, &head);
	debug_string(first);
}

void test_add_node_at() {
	struct s_node* a = new_node("windows", NULL, NULL);
	struct s_node* b = new_node("linux", NULL, NULL);
	struct s_node* c = new_node("osx", NULL, NULL);
	struct s_node* d = new_node("ubuntu", NULL, NULL);

	struct s_node* head = a;
	add_node_at(b, &head, 34);
	add_node_at(c, &head, 1);
	add_node_at(d, &head, 3);
	debug_string(head);
	my_int(count_s_nodes(head));
	my_char('\n');

	remove_last(&head);
	debug_string(head);
	remove_last(&head);
	debug_string(head);
	remove_last(&head);
	debug_string(head);
	remove_last(&head);
	debug_string(head);
}

void test_debug_char() {
	char x = 'a';
	char* xptr = &x;
	struct s_node* a = new_node(xptr, NULL, NULL);

	char y = 'b';
	char* yptr = &y;
	struct s_node* b = new_node(yptr, NULL, NULL);

	char z = 'c';
	char* zptr = &z;
	struct s_node* c = new_node(zptr, NULL, NULL);

	char xi = 'd';
	char* xiptr = &xi;
	struct s_node* d = new_node(xiptr, NULL, NULL);

	struct s_node* head;
	head = d;
	add_node(b, &head);

	add_node(c, &head);
	add_node(a, &head);

	debug_char(head);
}

void test_debug_int() {
	int a = 1;
	int* ap = &a;
	struct s_node* n1 = new_node(ap, NULL, NULL);

	int b = 2;
	int* bp = &b;
	struct s_node* n2 = new_node(bp, NULL, NULL);

	int c = 3;
	int* cp = &c;
	struct s_node* n3 = new_node(cp, NULL, NULL);

	int d = 4;
	int* dp = &d;
	struct s_node* n4 = new_node(dp, NULL, NULL);

	struct s_node* head = n1;
	add_node(n2, &head);
	add_node(n3, &head);
	add_node(n4, &head);

	debug_int(head);
}

void test_remove_node() {
	struct s_node* null_node = NULL;
	//null node
	void* elem1 = remove_node(NULL);
	if (elem1 == NULL) {
		printf("null\n");
	}
	else {
		printf("It's not null\n");
	}

	// null pointer
	void* elem2 = remove_node(&null_node);
	if (elem2 == NULL) {
		printf("null\n");
	}
	else {
		printf("It's not null\n");
	}

	// single node
	struct s_node* n1 = new_node("hello", NULL, NULL);
	debug_string(n1);
	char* elem3 = (char*) remove_node(&n1);
	printf("%s\n", elem3);
	debug_string(n1);
}

void test() {
	char c = 'a';
	char* cp = &c;
	struct s_node* a = new_node(cp, NULL, NULL);
	print_char(a);
	//printf("\n");
}

void test_traverse_char() {
	char x = 'a';
	char* xptr = &x;
	struct s_node* a = new_node(xptr, NULL, NULL);

	char y = 'b';
	char* yptr = &y;
	struct s_node* b = new_node(yptr, NULL, NULL);

	char z = 'c';
	char* zptr = &z;
	struct s_node* c = new_node(zptr, NULL, NULL);

	char xi = 'd';
	char* xiptr = &xi;
	struct s_node* d = new_node(xiptr, NULL, NULL);

	struct s_node* head;
	head = d; // end of list
	add_node(c, &head);
	add_node(b, &head);
	add_node(a, &head);

	traverse_char(head);
}

void test_traverse_int() {
	int a = 1;
	int* ap = &a;
	struct s_node* n1 = new_node(ap, NULL, NULL);

	int b = 2;
	int* bp = &b;
	struct s_node* n2 = new_node(bp, NULL, NULL);

	int c = 3;
	int* cp = &c;
	struct s_node* n3 = new_node(cp, NULL, NULL);

	int d = 4;
	int* dp = &d;
	struct s_node* n4 = new_node(dp, NULL, NULL);

	struct s_node* head = n1;
	add_node(n2, &head);
	add_node(n3, &head);
	add_node(n4, &head);

	traverse_int(head);
}

void test_traverse_string() {
	char x = 'a';
	char* xptr = &x;
	struct s_node* a = new_node(xptr, NULL, NULL);

	char y = 'b';
	char* yptr = &y;
	struct s_node* b = new_node(yptr, NULL, NULL);

	char z = 'c';
	char* zptr = &z;
	struct s_node* c = new_node(zptr, NULL, NULL);

	char xi = 'd';
	char* xiptr = &xi;
	struct s_node* d = new_node(xiptr, NULL, NULL);

	struct s_node* head;
	head = d; // end of list
	add_node(c, &head);
	add_node(b, &head);
	add_node(a, &head);

	traverse_string(head);
}

int main() {
	test_traverse_char();
	//test_traverse_int();
	return 0;
}