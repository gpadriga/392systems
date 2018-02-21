#include "my.h"

void my_num_base(int i, char * c) {
	if (!c || !*c) {
		my_str("Error: Please enter letters");
		return;
	}
	if (i < 0) {
		my_char('-');
	}
	long num = i;
	if (num < 0) {
		num *= -1;
	}
	long base = my_strlen(c);
	if (base == 1) { // unary case
		while (num--) {
			my_char(*c); // print out first char
		}
	}
	else {
		long cur = 1;
		while (cur <= num/base) { // grab first digit
			cur *= base;
		}
		// time to print
		while (cur != 0) {
			my_char(c[num/cur]);
			num = num % cur;
			cur /= base;
		}
	}
}