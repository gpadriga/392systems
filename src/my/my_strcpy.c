#include "my.h"
#include <stdio.h>

/* Copies the characters from src into dst
overwriting what's already in there.
Assume dst has enough room
*/
char* my_strcpy(char *dst, char *src) {
	if (!dst) {
		return NULL;
	}
	char * begin = dst; // retain ref to start of dst
	if (src) {
		int len = my_strlen(src);
		for (int i=0; i<len; i++) {
			char temp = *dst
			*dst = *src;
			dst++;
			src++;
			*src = temp;
		}
	}
	*dst = '\0'; // already checked if dst is null
	return begin;
}

/*
int main() {
	char test[6] = "hellox";
	char res[6] = "uhhhhh";
	my_strcpy(res, test);
	printf("%s", res);
	printf("\n");
	return 0;
}
*/