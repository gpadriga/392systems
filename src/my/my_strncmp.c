#include "my.h"

/*
Compares strings by ascii value for n chars or until end of a string
 If a and b are identical, return 0. 
 if a < b, return negative number 
 if a > b, return positive number
 Two NULL are equal.
 NULL is always less than a normal string
*/
int my_strncmp(char *a, char *b, int n) {
	if (n<1) {
		return 0;
	}
	while (a && b) {
		for (int i = 1; i < n; i++) { // compares n chars
			if (*a == *b) {
				a++;
				b++;
			}
			else {
				if (*a < *b) {
					return -1;
				}
				return 1;
			}
		}
		return 0;
	}
	if ( !a && !b ) {
		return 0;
	}
	if (!a) { // a is null
		return -1;
	}
	else return 1; // b is null
}
