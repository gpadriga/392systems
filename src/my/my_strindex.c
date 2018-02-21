#include "my.h"

int my_strindex(char* cptr, char c) {
	if (!cptr || !c) {
		return -1;
	}
	int i = 0;
	while (*cptr != '\0') {
	    if (*cptr == c) {
	      return i;
	    }
    	i++;
    	cptr++;
    }
	return -1;
}