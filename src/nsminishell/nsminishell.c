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
	int y,x;
	initscr();
	keypad(stdscr, TRUE);
	raw();
	noecho();
	scrollok(stdscr,1);
	// signals definition
	signal(SIGINT, doNothing);
	start_color();
	init_pair(1, COLOR_GREEN, COLOR_BLACK);
	init_pair(2, COLOR_CYAN, COLOR_BLACK);
	while (1) {
		// print prompt and current working directory
		char cwd[1024];
		int i = 0;
		attron(COLOR_PAIR(1));
		addstr("MINISHELL: ");
		attroff(COLOR_PAIR(1));
		attron(COLOR_PAIR(2));
		addstr(getcwd(cwd, sizeof(cwd)));
		addstr(" $: ");
		attroff(COLOR_PAIR(2));
		int buff = 10;
		char* input = malloc(buff*sizeof(char));
		int seen = 0;
		char* begin = input;
		seen++;
		char * newInput;
		char tempGet;
		while (1) {
			tempGet = getch();
			if (seen >= buff) {
				buff*=2;
				newInput = (char *) realloc(begin, buff*sizeof(char));
				begin = newInput;
			}
			else if (tempGet == 27) { // esc
				endwin();
				exit(1);
			}
			else if (i>0 && tempGet == 7) { // backspace
				getyx(stdscr, y, x);
				wmove(stdscr,y, x-1);
				refresh();
				delch();
				input[i]='\0';
				seen--;
				i--;
				}
			else if (tempGet == 7) {
				continue;
			}
			else if (tempGet != 10) { // if not enter
				input[i] = tempGet;
				addch(input[i]);
				i++;
				seen++;
			}
			else {
				break;
			}
		}

		addstr("\n");

		char ** dir = my_str2vect(begin);
		int sizeDir = my_vectsize(dir);

		// if nothing is entered
		if (sizeDir == 0) {
			printw("Please enter something, type help if you don't know anything\n");
		}

		// cd command
		else if (my_strcmp(dir[0], "cd") == 0) { // cd somepath
			if (chdir(dir[1]) == -1) {
				printw("Either that directory doesn't exist, or you're not allowed to access it\n");
			}
		}

		// help
		else if (my_strcmp(dir[0], "help") == 0 && sizeDir == 1) {
			printw("Here are things you can do: \n");
			printw("cd [directory] : Changes current working directory to what's specified\n");
			printw("ls : List the files and subdirectories in your current directory\n");
			printw("./[an executable] [some args] : Runs the executable with the given arguments\n");
			printw("exit : Exits the minishell\n");
			printw("help : You're already here!\n");
		}

		// exit
		else if (my_strcmp(dir[0], "exit") == 0 && sizeDir == 1) {
			printw("That's all folks!\n");
			return 1;
		}

		// no command matches or trying to exec or ls
		else {
			pid_t pid;
			char ans[9000];
			if ((pid = fork()) < 0) {
				perror("Child fork didn't work\n"), exit(1);
			}
			else if (pid == 0) { // child process
				signal(SIGINT, doQuit);
				dup2(1, 3000);
				if (execvp(dir[0], dir) == -1) {
					printw("Can't do that\n");
					exit(1);
				}
				else {
					read(3000, ans, 9000);
					addstr(ans);
				}
			}
			else { // parent
				wait(NULL);
			}
		}
	
	} // end of while
}
