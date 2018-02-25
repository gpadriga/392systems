#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include "my.h"

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
		my_str("Usage: ./pipes [message goes here]\n");
		return 1;
	}

	pid_t pid;
	int parent[2];
	int child[2];
	pipe(parent); // pipe 1
	pipe(child); // pipe 2

	if ( (pid = fork()) < 0) {
		perror("Child fork didn't work\n"), exit(1);
		return 1;
	} else if (pid == 0) { // child process
		pid_t gpid;
		if ( (gpid = fork()) < 0) {
			perror("Grandchild fork didn't work\n"), exit(1);
			return 1;
		}
		else if (gpid == 0) { // gchild
			close(child[1]); // don't write to child here
			// read string from child
			char cin[100] = "";
			read(child[0], cin, 100);
			// reverse string
			my_revstr(cin);
			my_str(cin);
			my_char('\n');
			exit(0);
		}
		else { // child
			char pin[100] = "";
			close(parent[1]); // don't write to parent here
			read(parent[0], pin, 100);
			char res[100] = "";
			for (int i = 0; i < my_strlen(pin); i++) {
				res[i] = forward(pin[i]);
			}
			my_str(res);
			my_char('\n');
			write(child[1], pin, 100);
			wait(NULL);
			exit(0);
		}
	}
	else { // parent process
		close(parent[0]);
		// convert cmd line args to string using vect2str
		char* input = my_vect2str(&argv[1]);
		// send strings to child
		write(parent[1], input, 100);
		wait(NULL);
		exit(0);
	}
	return 0; // yay u did it
}
