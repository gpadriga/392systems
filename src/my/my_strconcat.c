#include "my.h"

/* Takes two strings, a and b, allocates new memory, and concatenates the
	strings together */
char* my_strconcat(char* a, char* b) {
	// if a and b are null, return null
	if (!a && !b) {
		return NULL;
	}
	// if a is null, return copy of b
	if (!a) {
		return my_strdup(b);
	}
	// if b is null, return copy of a
	if (!b) {
		return my_strdup(a);
	}
	// Calculate the length of a and b
	int a_length = my_strlen(a);
	int b_length = my_strlen(b);
	// allocate new memory for a and b
	char* result = (char*) malloc((a_length + b_length + 1) * sizeof(char));
	// concatenate to the result
	my_strcat(result,a);
	my_strcat(result,b);
	// return result
	return result;
}