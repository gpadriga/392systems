#include "my.h"
#include <stdio.h>

void shakespeare() {
	char** list = my_str2vect("My bounty is as boundless as the sea, \
	My love as deep; the more I give to thee, \
	The more I have, for both are infinite.");
	for (int i = 0; i < 26; i++) {
		printf("%s\n", list[i]);
	}
	if (list[26] == NULL) {
		printf("It's null\n");
	}
	else {
		printf("not null\n");
	}
}

void null() {
	char** list = my_str2vect(NULL);
	if (list == NULL) {
		printf("null\n");
	}
	else {
		printf("not null\n");
	}
}

void empty() {
	char** list = my_str2vect("");
	if (list == NULL) {
		printf("list is null\n");
	}
	else if (list[0] == NULL) {
		printf("first elem is null\n");
	}
	else {
		printf("<%s>\n", list[0]);
	}
}

void whyarewestilldoingmy()  {
	char* list[] = {"hello", "bye", NULL};
	printf("%d\n", my_vectsize(list));
}

int main() {
	// char** array = my_str2vect("Hello world");
	// printf("%s\n", array[0]);
	// printf("%s\n", array[1]);
	// if (array[2] == NULL) {
	// 	printf("NULL\n");
	// }
	// else {
	// 	printf("not null\n");
	// }
	//shakespeare();
	//null();
	//empty();
	whyarewestilldoingmy();
	return 0;
}