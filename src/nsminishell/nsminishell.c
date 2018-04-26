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
	int clipi = 0;
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
	int wu = 0;
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
		char clipboard[9000];
		char* input = malloc(buff*sizeof(char));
		int seen = 0;
		char* begin = input;
		seen++;
		char * newInput;
		int tempGet;
		while (1) {
			tempGet = getch();
			if (seen >= buff) {
				buff*=2;
				newInput = (char *) realloc(begin, buff*sizeof(char));
				begin = newInput;
			}
			else if (tempGet == 23 && i>0) { // CTRL-W
				if (wu != 1) {
					wu = 1;
					clipi = 0;
					// reset clipboard 
				}
				char readch=' ';
				while ( (readch == ' ')  && i>0) {
					readch = inch() & A_CHARTEXT;
					clipboard[clipi] = readch;
					delch();
					getyx(stdscr, y, x);
					wmove(stdscr,y, x-1);
					refresh();
					i--;
					clipi++;
					seen--;
				}
				while ( readch != ' ' && readch != '\t' && i>0) {
					readch = inch() & A_CHARTEXT;
					clipboard[clipi] = readch;
					if (readch != ' ' && i>0) {
						delch();
						getyx(stdscr, y, x);
						wmove(stdscr,y, x-1);
						refresh();
					}
					i--;
					clipi++;
					seen--;
					//addstr("second loop");
				}
				//i++;
				getyx(stdscr, y, x);
				wmove(stdscr,y, x+1);
				refresh();
			}
			else if (tempGet == 21 && i>0) { // CTRL-U cut whole line
				if (wu != 1) {
					wu = 1;
					clipi = 0;
					//reset clipboard 
					bzero(clipboard, 9000);
				}
				char readch=' ';
				while (i >=0) {
					readch = inch() & A_CHARTEXT;
					clipboard[clipi] = readch;
					delch();
					getyx(stdscr, y, x);
					wmove(stdscr,y, x-1);
					refresh();
					i--;
					clipi++;
					seen--;
				}
				getyx(stdscr, y, x);
				wmove(stdscr,y, x+1);
				refresh();
				//delch();
				//delch();
			}
			else {
				wu = 0;
			}
			if (tempGet == 27) { // esc
				endwin();
				exit(1);
			}
			else if (tempGet == KEY_LEFT && i>0) {
				getyx(stdscr, y, x);
				wmove(stdscr, y, x-1);
				refresh();
				i--;
			}
			else if (tempGet == KEY_LEFT) {
				continue;
			}
			else if (tempGet == KEY_RIGHT && i < seen-1) {
				getyx(stdscr, y, x);
				wmove(stdscr, y, x+1);
				refresh();
				i++;
			}
			else if (tempGet == KEY_RIGHT) {
				continue;
			}
			else if (i>0 && tempGet == KEY_BACKSPACE) { // backspace
				getyx(stdscr, y, x);
				wmove(stdscr,y, x-1);
				refresh();
				delch();
				input[i]='\0';
				seen--;
				i--;
			}
			else if (tempGet == KEY_BACKSPACE) {
				continue;
			}
			else if (tempGet == KEY_UP) {
				continue;
			}
			else if (tempGet == KEY_DOWN) {
				continue;
			}
			else if (tempGet == 21) {
				continue;
			}
			else if (tempGet == 1) { // CTRL-A
				getyx(stdscr, y, x);
				wmove(stdscr, y, x-i);
				refresh();
				i=0;
			}
			else if (tempGet == 5) { // CTRL-E
				getyx(stdscr, y, x);
				wmove(stdscr, y, x+(seen-i-1));
				refresh();
				i=seen-1;
			}
			else if (tempGet == 12) { // CTRL-L
				getyx(stdscr, y, x);
				wscrl(stdscr, y);
				wmove(stdscr, 0, x);
				refresh();
			}

			else if (tempGet == 25) { // CTRL-Y paste
				// reverse clipboard contents
				int length = my_strlen(clipboard);
				seen += length;
				i += length;
				for (int j = length-1; j >=0; j--) {
					addch(clipboard[j]);
				}
			}

			else if (tempGet == 23) {
				continue;
			}
			else if (tempGet != 10 && i == seen-1) { // if not enter and at end
				input[i] = tempGet;
				addch(input[i]);
				i++;
				seen++;
			}
			else if (tempGet != 10) { // not enter and in middle of string 
				chtype chstr[9000];
				getyx(stdscr, y, x);
				inchstr(chstr);
				char result[9000];
				for (int j = 0; j<9000; j++) {
					result[j]= chstr[j] & A_CHARTEXT; // convert bitmask to char
				}
				addch(tempGet);
				i++;
				seen++;	
				addstr(result);
				move(y,x+1);
				refresh();
			}
			else { // enter
				getyx(stdscr, y, x);
				wmove(stdscr, y, x+(seen-i-1));
				refresh();
				i=seen-1;
				break;
			}
		}

		addstr("\n");
		// parse the input using inchstr

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
