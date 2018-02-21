#include "my.h"
/* Takes a string a and a string b, and concatenates them together.
   Copies the entire string of a to a new location in memory. Copies the first
   n characters of b onto the end of the new string. If n is greater than b,
   copies the entire b string. If n is negative, treats it as 0*/
char* my_strnconcat(char* a, char* b, int n) {
	// if a and are both null, return null
	if (!a && !b) {
		return NULL;
	}
	// if b is null, copy a
	if (!b) {
		return my_strdup(a);
	}
	int b_length = my_strlen(b);
	// if n is negative, treat it as 0
	if (n < 0) {
		n = 0;
	}
	// finds number of b characters to add
	int num_b_chars = n < b_length ? n : b_length;
	// if a is null, copy num_b_chars of b and returns it
	if (!a) {
		char* b_result = (char*) malloc((num_b_chars + 1) * sizeof(char));
		char* cur_b_res = b_result;
		for (int i = 0; i < num_b_chars; i++) {
			*cur_b_res = *b;
			cur_b_res++;
			b++;
		}
		*cur_b_res = '\0';
		return b_result;
	}
	// otherwise, copies a into result
	int a_length = my_strlen(a);
	char* ab_result = (char*) malloc((a_length + num_b_chars + 1) * 
		sizeof(char));
	char* cur_ab_res = ab_result;
	my_strcat(ab_result, a);
	cur_ab_res += a_length;
	// copies the appropriate characters of b
	for (int i = 0; i < num_b_chars; i++) {
		*cur_ab_res = *b;
		cur_ab_res++;
		b++;
	}
	*cur_ab_res = '\0';
	return ab_result;
}