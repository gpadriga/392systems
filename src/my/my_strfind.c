#include "my.h"

/*
Returns a pointer to the first char in the string which matches.
Return NULL if the letter is not found.
*/
char* my_strfind(char *s, char c) {
	if (s && c) {
		while (*s != '\0') {
			if (*s == c) {
				return s;
			}
			s++;
		}
		return NULL;
	}
	return NULL;
}
