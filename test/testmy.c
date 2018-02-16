#include "my.h"
#include <stdlib.h>
#include <stdio.h>

int main()
{
	my_str("hi");
	printf("\n");
	my_str("");
	printf("\n");
	my_str("Did you ever hear the tragedy of Darth Plagueis The Wise?";)
	printf("\n");
	my_str("weewoo";)
	printf("\n");
	printf("\n");

	my_int(256);
	printf("\n");
	//my_int(-257);
	printf("\n");
	my_int(0);
	printf("\n");
	printf("\n");

	printf(my_strindex("hello", 'l'));
	printf("\n");
	printf("\n");

	printf(my_strrindex("hello", 'l'));
	printf("\n");
	printf("\n");

	my_strlen("hello");
	printf("\n");
	printf("\n");

	string test = "hello";
	my_revstr(test);
	printf(test);
	return 0;
}