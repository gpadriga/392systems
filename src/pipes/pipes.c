#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>

/*
need to import my library to print and add my_vect2str.c
*/

char forward(char c) {
	if (c == 'Z') {
		c = 'A';
	}
	else if (c == 'z') {
		c = 'a';
	}
	else if (c < 101 || c > 172) { // c is a non letter
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

int main(int argc, char *argv[]) { // take in cmd line args
	pid_t pid;
	int parent[2];
	int child[2];
	int gchild[2];
	pipe(parent);
	pipe(child);

	if ( (pid = fork()) < 0) {
		perror("fork didnt work"), exit(1);
	} else if (pid == 0) { // child
		pipe(gchild);
	else {

	}
	return 0;
}