#include <stdio.h>
#include "my.h"

void nullCases() {
	// null pointer
	if (my_vect2str(NULL) == NULL) {
		printf("It's null!\n");
	}
	else {
		printf("It's not null!\n");
	}
	// null string
	char* string = NULL;
	char** pointer = &string;
	if (my_vect2str(pointer) == NULL) {
		printf("It's null!\n");
	}
	else {
		printf("It's not null!\n");
	}
}

void singleString() {
	char* pointer2[] = {"asteroid", NULL};
	printf("%s!\n", my_vect2str(pointer2));
}

void doubleStrings() {
	char* duo[] = {"asteroid", "meteor", NULL};
	printf("%s!\n", my_vect2str(duo));
}

void multiStrings() {
	char* multi[] = {"asteroid", "meteor", "black hole", "supernova", "galaxy",
	"comet", "quasar", NULL};
	printf("%s!\n", my_vect2str(multi));
}

void commandLine(char* argv[]) {
	printf("%s!\n", my_vect2str(argv));
}

int main(int argc, char* argv[]) {
	// null cases
	nullCases();
	// single string
	singleString();
	// two strings
	doubleStrings();
	// bunch of strings
	multiStrings();
	// test with command line arguments
	commandLine(&argv[1]);
	return 0;
}