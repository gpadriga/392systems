#include "my.h"

int my_vectsize(char ** vect) {
	int res = 0;
	if (vect != NULL) {
		while(*vect != NULL) {
			res++;
			vect++;
		}
		return res;
	}
	return res;
}