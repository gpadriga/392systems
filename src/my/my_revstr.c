#include "my.h"

int my_revstr(char * c) {
	int len = my_strlen(c);
	if (len > 1) {
		for (int j = 0, half = len/2; j< half; j++) {
			char temp = c[j];
			c[j] = c[len - 1 - j];
			c[len - 1 - j] = temp;
		}
	}
	return len;
}