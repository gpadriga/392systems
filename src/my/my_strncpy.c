#include "my.h"
#include <stdio.h>

/* Copies n characters from src into dst
overwriting what's already in there
ask about what to return
*/
char* my_strncpy(char *dst, char *src, int n) {
	if (n < 1) { // if not copying anything over
		return dst;
	}
	if (n >= my_strlen(src)) { // if copying whole thing anyway
		return my_strcpy(dst, src); // already wrote something that does that
	}
	if (!dst) {
		return NULL;
	}
	char * begin = dst; // retain ref to start of dst
	if (src) {
		for (int i = 1; i<=n; i++) {
			*dst = *src;
			dst++;
			src++;
		}
	}
	*dst = '\0';
	return begin;
}

/*
int main() {
	char *src = NULL;
	char *dst = NULL;
	char *res = my_strncpy(dst, src, 5);
	//my_strncpy(dst, src, 5);
	printf("%s", dst);
	printf("\n");
	printf("%s", res);
	printf("\n");
	return 0;
}
*/