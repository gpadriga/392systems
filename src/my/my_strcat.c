#include "my.h"
/* Jordan Tantuico and Gabby Padriga
   I pledge my honor that I have abided by the Stevens Honor System.*/

/* Copies the string in src to the end of dst, assumes there is enough memory
   in dst to fit both dst and src*/
char* my_strcat(char *dst, char *src) {
	// if dst is null, return null
	if (!dst) {
		return NULL;
	}
	// if src is null, return dst
	if (!src) {
		return dst;
	}
	// navigate to the end of dst
	char *cur_dst = dst;
	int len_dst = my_strlen(dst);
	cur_dst += len_dst;
	// copy src into cur_dst
	my_strcpy(cur_dst, src);
	return dst;
}