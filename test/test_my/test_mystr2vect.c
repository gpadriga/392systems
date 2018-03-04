#include "my.h"
#include <stdio.h>

int main() {
	char** array = my_str2vect("Hello world");
	printf("%s\n", array[0]);
	printf("%s\n", array[1]);
	printf("%s\n", array[2]);
}