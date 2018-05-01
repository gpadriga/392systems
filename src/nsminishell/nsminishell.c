#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include "my.h"
#include <signal.h>
#include <sys/wait.h>
#include <ncurses.h>
#include <string.h>
#include "list.h"
#include <fcntl.h>

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
	struct s_node* initial = NULL;
	struct s_node ** head = &initial;
	char readbuf [9000];

	// load past history, if any
	
	FILE *fptr = fopen(".nsmshistory", "r+");
	while (!feof(fptr)) {
		if (fgets(readbuf, 9000, fptr) != NULL) {
			char * readstr = my_strdup(readbuf);
			struct s_node* loadedcmd = new_node(readstr, NULL, NULL);
			add_node(loadedcmd, head);
			bzero(readbuf, 9000);
		}
		else {
			break;
		}
	}

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
		int nodeIndex = 0;
		while (1) {
			//debug_string(*head);
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
			else if (tempGet == KEY_UP) { // Up arrow
				if (count_s_nodes(*head) ==0) {
					continue;
				}
				else {
					getyx(stdscr, y, x);
					wmove(stdscr,y, x-i);
					refresh();
					wclrtoeol(stdscr);
					getyx(stdscr, y, x);
					if (nodeIndex != count_s_nodes(*head)) {
						nodeIndex++;
					}
					char * toPrint= (char *) elem_at(*head, nodeIndex);
					addstr(toPrint);
					i = my_strlen(toPrint)-1;
					seen = i;
					//printw("%d\n",i);
					//printw("%d\n",seen);
					wmove(stdscr, y, x+i);
					refresh();
				}
			}
			else if (tempGet == KEY_DOWN) { // down arrow
				if (count_s_nodes(*head) ==0) {
					continue;
				}
				else {
					getyx(stdscr, y, x);
					wmove(stdscr,y, x-i);
					refresh();
					wclrtoeol(stdscr);
					getyx(stdscr, y, x);
					if (nodeIndex != 0) {
						nodeIndex--;
					}
					char * toPrint= (char *) elem_at(*head, nodeIndex);
					addstr(toPrint);
					i = my_strlen(toPrint) - 1;
					seen = i;
					wmove(stdscr, y, x+i);
					refresh();
				}
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
			else if (tempGet == 12) { // CTRL-L clear screen
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

		//addstr("\n");
		// parse the input using inchstr
		getyx(stdscr, y, x);
		wmove(stdscr, y, x-i);


		chtype userIn[9000];
		char userChars[9000];
		inchnstr(userIn,seen);
		i=0;
		for (int j = 0; j<9000; j++) {
			userChars[j]= userIn[j] & A_CHARTEXT; // convert bitmask to char
		}
		char * command = strdup(userChars);
		struct s_node * userNode = new_node(command, NULL, NULL);
		add_node(userNode, head);
		nodeIndex=0;

		addstr(userChars);
		getyx(stdscr, y, x);
		wmove(stdscr,y+1,0);
		refresh();

		char ** dir = my_str2vect(userChars);
		int sizeDir = my_vectsize(dir);

		// if nothing is entered
		if (sizeDir == 0) {
			printw("Please enter something, type help if you need it\n");
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
			for (int j = 0; j < count_s_nodes(*head); j++) {
				fprintf(fptr, "%s\n", (char *) elem_at(*head, j));
			}
			fclose(fptr);
			printw("That's all folks!\n");
			endwin();
			return 1;
		}

		else if (my_strncmp(dir[0], "$(", 2) == 0 && sizeDir == 1) {
			addstr("Bonelli says: Implement me!\n");
		}

		// no command matches or trying to exec or ls
		else {
			pid_t pid;
			int pipefd[2];
			pipe(pipefd);
			char ans[9000];
			if ((pid = fork()) < 0) {
				perror("Child fork didn't work\n"), exit(1);
			}
			else if (pid == 0) { // child process
				signal(SIGINT, doQuit);
				close(pipefd[0]);
				dup2(pipefd[1], 1);
				close(pipefd[1]);
				if (execvp(dir[0], dir) == -1) {
					printw("Can't do that\n");
					exit(1);
				}
				exit(1);
			}
			else { // parent
				close(pipefd[1]);
				wait(NULL);
				read(pipefd[0], ans, 9000);
				//addstr("\n");
				addstr(ans);
				bzero(ans, 9000);
			}
		}
	
	} // end of while
}
