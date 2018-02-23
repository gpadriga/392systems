#include <unistd.h>
#include <stdio.h>
#include <string.h>

struct block {
	int free; // 1 if free, 0 if not
	void* begin;
	void* end;
}

block make_block(int bol, void* beg, void* end) {
	struct block mem;
	mem.free = bol;
	mem.begin = beg;
	mem.end = end;
	return mem;
}

/*
keeps track of the location of the program break,
uses sbrk(2) to increment it, and 
returns a pointer to newly allocated block of memory.
*/
void* my_malloc(int n) {
	int alloc = n + sizeof(struct block);
	void* start = sbrk(0);
	void* end = sbrk(alloc);
	*(struct block*) start = make_block(0, start, end);
	return start;
}

/*
allocates memory for an array of num objects of size size
and initializes all bytes in the allocated storage to zero.
*/
void* my_calloc(int num, int size) {
	int mult = num*size;
	void* res = my_malloc(mult);
	void* hold = res;
	for (int i = 0; i < mult; i++) {
		*(int*) res = 0;
		res++;
	}
	return hold;
}

/*
mark blocks as free, and will move the break to free RAM
back to the OS when appropriate (i.e. when the last blocks
have been freed).
*/
void my_free(void* ptr) {
	brk(ptr);
}

int main() {
	char* result = (char*) my_malloc(10);
	strcpy(result, "heeellloo");
	printf("%s\n", result);

	void* test_calloc = my_calloc(3,3);
	for (int i = 0; i < 9; i++) {
		printf("%d\n", *(int*) test_calloc);
		test_calloc++;
	}
	return 0;
}