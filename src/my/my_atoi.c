#include "my.h"
/* Takes in a string n and returns the int value that is contained within it.
   Accounts for negative signs, ignores preceding/trailing characters*/
int my_atoi(char *n) {
	// if n == null, return 0
	if (!n) {
		return 0;
	}
	// establishes a counter for the number of negative signs
	int neg_count = 0;
	// until you reach a non-zero number, progress to the next character
	while ((*n <= '0' || *n > '9') && *n != '\0') {
		// if there's a negative sign, increment the negative count
		if (*n == '-') {
			neg_count++;
		}
		n++;
	}
	// if there were no numbers found, return 0
	if (*n == '\0') {
		return 0;
	}
	// starts result out as negative
	int result = -(*n - 48);
	n++;
	// while *n is a number (including 0), add the current number
	while (*n >= '0' && *n <= '9') {
		result = (result * 10) - (*n - 48);
		n++;
		//printf("Infinite loop 5\n");
	}
	// if there is an even number of negatives, switch to positive
	if (!(neg_count & 1)) {
		result *= -1;
	}
	return result;
}