#include "my.h"
#include <stdio.h>

int main() {
	char * test = "hello";
	printf("%s", test);
	printf("\n");
	my_revstr(test);
	printf("%s", test);
	return 0;
}
