#include "my.h"
#include <stdio.h>

int main() {
	/* Test cases for my_str
		my_str(NULL) -> do nothing
		my_str("") -> print ""
		my_str(" ") -> print " "
		my_str("'") -> print "'"
		my_str("a") -> print "a"
		my_str("5") -> print "5"
		my_str("-5") -> print "-5"
		my_str("@") -> print "@"
		my_str("hello") -> print "hello"
		my_str("goodbye") -> print "goodbye"
		my_str("12345") -> print "12345"
		my_str("@#$%&^$%@#$%") -> print "@#$%&^$%@#$%"
		my_str("heaselk@#$%@#$398adjfkl") -> print "heaselk@#$%@#$398adjfkl"
		my_str("odd") -> print "odd"
		my_str("even") -> print "even"
		my_str("hello\0") -> print "hello\0"
		my_str("he\0llo") -> print "he\0llo"

	*/
	// printf("Test cases for my_str:\n");
	// char * test_array[20] = {NULL, "", " ", "'", "a", "5", "-5", "@", 
	// "hello", "goodbye", "12345", "@#$%&^$%@#$%", "heaselk@#$%@#$398adjfkl",
	// "odd", "even", "hel\\0lo"};

	// for (int i = 0; i < 16; i++) {
	// 	my_str("The word is \"");
	// 	my_str(test_array[i]);
	// 	my_str("\"");
	// 	printf("\n");
	// }

	/* Test cases for my_int 
		0
		1
		2
		5
		10
		13
		20
		25
		54
		100
		134
		200
		1000
		1234
		34578234
		2147483647
		-1
		-2
		-5
		-10
		-13
		-20
		-50
		-65
		-100
		-134
		-1000
		-1234
		-50000
		-100000
		-1000000
		-12343745
		-2147483648
	*/

	int array[] = {0,1,2,5,10,13,20,25,54,100,134,200,1000,1234,34578234,2147483647,
		-1,-2,-5,-10,-13,-20,-50,-65,-100,-134,-1000,-1234,-50000,-100000,-1000000,-12343745,
		-2147483648};
	for (int i = 0; i < 33; i++) {
		my_str("The number is ");
		my_int(array[i]);
		printf("\n");
	}

	return 0;
}