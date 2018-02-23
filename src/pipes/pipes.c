#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include "my.h"

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
	else if (c < 65 || c > 123) { // c is a non letter
		return c;
	}
	else {
		c++;
	}
	return c;
}

int main(int argc, char *argv[]) { // take in cmd line args
	if (argc <= 1) {
		my_str("Usage: ./pipes message\n");
		return 1;
	}

	pid_t pid;
	int parent[2];
	int child[2];
	//int gchild[2];
	pipe(parent);
	pipe(child);

	if ( (pid = fork()) < 0) {
		perror("fork didnt work"), exit(1);
	} else if (pid == 0) { // child process
		/*
		pid_t gpid;
		gpid = fork();
		pipe(gchild);
		*/
	}
	else { // parent process
		// send cmd line args as a string to child
	}
	return 0;
}