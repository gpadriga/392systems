#include "my.h"

void my_str(char* c) {
	if (c) {
		while (*c != '\0') {
		    my_char(*c);
		    c++;
		  }
	}
}