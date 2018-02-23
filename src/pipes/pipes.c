#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>

char forward(char c) {
	if (c == 'Z') {
		c = 'A';
	}
	else if (c == 'z') {
		c = 'a';
	}
	else if (c<101 || c>172) {
		return c;
	}
	else {
		c++;
	}
	return c;
}

char rev(char c) {
	if (c == 'A') {
		c = 'Z';
	}
	else if (c == 'a') {
		c = 'z';
	}
	else if (c < 101 || c > 172) { // c is a non-letter
		return c;
	}
	else {
		c--;
	}
	return c;
}

int main() {
	return 0;
}