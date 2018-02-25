// Created on 2/23/2018
// Last modified on 2/25/2018
// Latest changes: implemented function
#include "my.h"

/* Transforms a list of strings into a single string separated by spaces */
char* my_vect2str(char **x) {
	// if x is null or *x is null, return null
	if (x == NULL || *x == NULL) {
		return NULL;
	}
	// create a new string to hold the result, max of 100 characters
	char* result = (char*)malloc(100 * sizeof(char));
	while (x != NULL && *x != NULL) {
		// cat current to result
		my_strcat(result, *x);
		x++;
		// if current is not null, add a space to result
		if (x != NULL && *x != NULL) {
			my_strcat(result, " ");
		}
	}
	// return the result
	return result;
}