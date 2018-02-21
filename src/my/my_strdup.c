#include "my.h"

/* Takes a string str, allocates new memory, and copies the string to the new
	memory */
char* my_strdup(char* str) {
	// if str is null, return null
	if (!str) {
		return NULL;
	}
	// allocates new memory based on the size of str
	int str_len = my_strlen(str);
	char* dup = (char*) malloc((str_len + 1) * sizeof(char));
	// copies str onto the new string
	my_strcat(dup, str);
	// returns a pointer to the new string
	return dup;
}

