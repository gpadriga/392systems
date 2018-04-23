#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/wait.h>
#include <ncurses.h>
#include <string.h>

int main() {
	int y,x;
	initscr();
	keypad(stdscr, TRUE);
	raw();
	scrollok(stdscr,1);
	int tempGet;
	while (1) {
		tempGet = getch();
		if (tempGet == 27) {
			endwin();
			exit(1);
		}
		if (tempGet == 10) {
			chtype chstr[9000];
			char result[9000];
			getyx(stdscr, y,x);
			move(y,0);
			inchstr(chstr);
			for (int j = 0; j<9000; j++) {
				result[j]= chstr[j] & A_CHARTEXT; // convert bitmask to char
			}
			move(y+1, 0);
			refresh();
			addstr(result);
			move(y+2, 0);
			refresh();
		}
	}
}