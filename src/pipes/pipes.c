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
		my_str("Usage: ./pipes message");
		return 1;
	}

	pid_t pid;
	int parent[2];
	int child[2];
	pipe(parent); // pipe 1
	pipe(child); // pipe 2

	if ( (pid = fork()) < 0) {
		perror("Child fork didn't work"), exit(1);
	} else if (pid == 0) { // child process
		/*
		pid_t gpid;
		if ( (gpid = fork()) < 0) {
			perror("Grandchild fork didn't work"), exit(1);
		}
		else if (gpid == 0){ // fork went ok
			// read string from child
			// reverse string and print it
		}
		else 
		*/
		char in[100] = "";
		while (read(parent[0], in, 100) > 0) {
			forward(in);
		}
		char send[100] = in;
		// forward in
		write 

	}
	else { // parent process
		// convert cmd line args to string using vect2str
		// send strings to child
	}
	return 0; // yay u did it
}#include <stdio.h>
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
		my_str("Usage: ./pipes message");
		return 1;
	}

	pid_t pid;
	int parent[2];
	int child[2];
	pipe(parent); // pipe 1
	pipe(child); // pipe 2

	if ( (pid = fork()) < 0) {
		perror("Child fork didn't work"), exit(1);
	} else if (pid == 0) { // child process
		/*
		pid_t gpid;
		if ( (gpid = fork()) < 0) {
			perror("Grandchild fork didn't work"), exit(1);
		}
		else if (gpid == 0){ // fork went ok
			// read string from child
			// reverse string and print it
		}
		else 
		*/
		char in[100] = "";
		while (read(parent[0], in, 100) > 0) {
			forward(in);
		}
		char send[100] = in;
		// forward in
		write 

	}
	else { // parent process
		// convert cmd line args to string using vect2str
		// send strings to child
	}
	return 0; // yay u did it
}
