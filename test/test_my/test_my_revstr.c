#include "my.h"
#include <stdio.h>

void nullPointer() {
	char* null = NULL;
	my_revstr(null);
	printf("%p\n", null);
}

void emptyString() {
	char a[] = "";
	my_revstr(a);
	printf("%s!\n", a);
}

void singleCharacter() {
	char a[] = "a";
	my_revstr(a);
	printf("%s!\n", a);
}

void doubleCharacter() {
	char a[] = "ab";
	my_revstr(a);
	printf("%s!\n", a);
}

void fiveCharacter() {
	char a[] = "abcde";
	my_revstr(a);
	printf("%s!\n", a);
}

void sixCharacter() {
	char a[] = "abcdef";
	my_revstr(a);
	printf("%s!\n", a);
}

int main() {
	nullPointer();
	emptyString();
	singleCharacter();
	doubleCharacter();
	fiveCharacter();
	sixCharacter();
	return 0;
}