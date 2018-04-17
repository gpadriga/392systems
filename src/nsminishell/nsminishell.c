#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include "my.h"
#include <signal.h>
#include <sys/wait.h>
#include <ncurses.h>
#include <string.h>

/*	Gabrielle Padriga and Jordan Tantuico
	We pledge our honor that we have abided by the Stevens Honor System
*/

void doNothing(int n) { }
void doQuit(int n) {
	exit(1);
}

int main() {
	initscr();
	keypad(stdscr, TRUE);
	raw();
	// signals definition
	signal(SIGINT, doNothing);
	while (1) {
		// print prompt and current working directory
		char cwd[1024];
		int i = 0;
		printw("MINISHELL: ");
		printw(getcwd(cwd, sizeof(cwd))); 
		printw(" $: ");
		int buff = 10;
		char* input = malloc(buff*sizeof(char));
		int seen = 0;
		char* begin = input;
		read(0, input, 1);
		seen++;
		char * newInput;
		while (input[i] != '\n') {
			if (seen >= buff) {
				buff*=2;
				newInput = (char *) realloc(begin, buff*sizeof(char));
				begin = newInput;
			}
			input++;
			seen++;
			input[i] = getch();
			i++;
		}

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

		// no command matches or trying to exec or ls
		else {
			pid_t pid;
			if ((pid = fork()) < 0) {
				perror("Child fork didn't work\n"), exit(1);
			}
			else if (pid == 0) { // child process
				signal(SIGINT, doQuit);
				if (execvp(dir[0], dir) == -1) {
					my_str("Can't do that\n");
					exit(1);
				}
				else {
					exit(1);
				}
			}
			else { // parent
				wait(NULL);
			}
		}
	}
}
