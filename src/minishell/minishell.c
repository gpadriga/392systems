#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include "my.h"
#include <signal.h>
#include <sys/wait.h>

/*	Gabrielle Padriga and Jordan Tantuico
	We pledge our honor that we have abided by the Stevens Honor System
Things that may be useful:
	int chdir (const char *path) : changes current working directory
	char* get_current_dir_name(void) : self explanatory, for debugging
	int execvp (const char *file, char *const argv[]) : created child
		process does not have to run the same program as the parent process
		does. The exec type system calls allow a process to run any program files,
		which include a binary executable or a shell script
		file: points to the file name associated with the file being executed.
		argv:  is a null terminated array of character pointers.
*/

void doNothing(int n) { }

int main() {
	// signals definition
	signal(SIGINT, doNothing);
	while (1) {
		// print prompt and current working directory
		char cwd[1024];
		my_str("MINISHELL: ");
		my_str(getcwd(cwd, sizeof(cwd))); 
		my_str(" $: ");
		int buff = (10);
		char* input = malloc(buff*sizeof(char));
		int seen = 0;
		char* begin = input;
		read(0, input, 1);
		seen++;
		char * newInput;
		while (*input != '\n') {
			if (seen >= buff) {
				buff*=2;
				newInput = (char *) realloc(begin, buff*sizeof(char));
				begin = newInput;
			}
			input++;
			seen++;
			read(0, input, 1);
		}
		//my_str("this is what's in our directions string: ");
		//my_str(begin);
		//my_str("\n");
		char ** dir = my_str2vect(begin);
		int sizeDir = my_vectsize(dir);

		// if nothing is entered
		if (sizeDir == 0) {
			my_str("Please enter something, type help if you don't know anything\n");
		}

		// cd command
		else if (my_strcmp(dir[0], "cd") == 0) { // cd somepath
			if (chdir(dir[1]) == -1) {
				my_str("Either that directory doesn't exist, or you're not allowed to access it\n");
			}
		}

		// ls command
		else if (my_strcmp(dir[0], "ls") == 0 && sizeDir == 1) {
			pid_t pid;
			if ((pid = fork()) < 0) {
				perror("Child fork didn't work\n"), exit(1);
			}
			else if (pid == 0) { // child process
				const char* cmd = "ls";
				char *arr[2];
				arr[0]= "ls";
				arr[1]= NULL;
				execvp(cmd,arr);
				exit(0);
			}
			else { // parent
				wait(NULL);
			}
		}

		// help
		else if (my_strcmp(dir[0], "help") == 0 && sizeDir == 1) {
			my_str("Here are things you can do: \n");
			my_str("cd [directory] : Changes current working directory to what's specified\n");
			my_str("ls : List the files and subdirectories in your current directory\n");
			my_str("./[an executable] [some args] : Runs the executable with the given arguments\n");
			my_str("exit : Exits the minishell\n");
			my_str("help : You're already here!\n");
		}

		// exit
		else if (my_strcmp(dir[0], "exit") == 0 && sizeDir == 1) {
			my_str("That's all folks!\n");
			return 1;
		}

		// exec function
		else if (my_strcmp(dir[0], "./idunnoyet") == 0) { // I dunno how we're gonna implement this {
			//use execvp and str2vect to pass args
			// fork before execvp
			pid_t pid;
			if ((pid = fork()) < 0) {
				perror("Child fork didn't work\n"), exit(1);
			}
			else if (pid == 0) { // child process

			}
		}

		// no command matches or trying to exec
		else {
			char ** cmnds = (dir)++; // how to cut off first word in vector?
			my_str(cmnds[0]);
			if (execvp(dir[0], cmnds) == -1) {
				my_str("Ya can't do that!\n");
			}
		}
		/* we don't need to worry about memory freeing apparently
		for (int i = 0; i < sizeDir; i++) {
			my_str(dir[i]);
			my_str(" ");
		}
		for (int i = 0; i <= sizeDir; i++) {
			printf("%s\n", "freeing ");
			printf("%d\n", i);
			free(dir[i]);
		}
		*/
		/*
		free(dir);
		free(begin);
		free(input);
		free(newInput);
		*/
	}
}
