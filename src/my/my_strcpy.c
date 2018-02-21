#include "my.h"

/* Copies the characters from src into dst
overwriting what's already in there.
Assume dst has enough room
ask about what to return
*/
char* my_strcpy(char *dst, char *src) {
	if (!dst) {
		return NULL;
	}
	char * begin = dst; // retain ref to start of dst
	if (src) {
		int len = my_strlen(src);
		for (int i = 0; i < len; i++) {
			*dst = *src;
			dst++;
			src++;
		}
	}
	*dst = '\0';
	return begin;
}
