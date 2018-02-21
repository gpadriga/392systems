#include "my.h"

/*
Returns a pointer to the last char in the string which matches.
Return NULL if the letter is not found.
*/
char* my_strrfind(char *s, char c) {
	if (s && c) {
		char * res = NULL;
		while (*s != '\0') {
			if (*s == c) {
				res = s;
			}
			s++;
		}
		return res;
	}
	return NULL;
}
