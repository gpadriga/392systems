#include "my.h"

/*
Compares strings by ascii value character by character
 If a and b are identical, return 0. 
 if a < b, return negative number 
 if a > b, return positive number
 Two NULL are equal.
 NULL is always less than a normal string
*/
int my_strcmp(char *a, char *b) {
	if (a && b) { // a and b are both not null
		while (*a != '\0' && *b != '\0') { // while both not null
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
		} // after while loop, at least 1 is \0
		if (*a == '\0' && *b == '\0') { //both term and eqiv
			return 0;
		}
		else if (*a == '\0') { // a hit end before b
			return -1;
		}
		else { // a < b
			return 1;
		}
	}
	if (!a && !b) {
		return 0;
	}
	if (!a) { // a is null
		return -1;
	}
	else return 1; // b is null
}
