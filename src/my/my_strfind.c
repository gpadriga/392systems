#include "my.h"
#include <stdio.h>

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

/*
int main() {
	char test[5] = "hello";
	char res = *(my_strfind(test, 'l'));
	my_char(res);
	return 0;
}
*/