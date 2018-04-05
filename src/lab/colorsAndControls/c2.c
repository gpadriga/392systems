#include <stdlib.h>
#include <ncurses.h>
#include <strings.h>

// gcc c2.c -lncurses -o cnc

/**
	Ctrl-b : enable bold mode
Ctrl-i : enable italicized text mode
Ctrl-l : enable blinking text mode
Ctrl-r : reset all style to defaults
Ctrl-u : enable underline mode
**/

int main() {
	initscr();
	keypad(stdscr, TRUE);   /* enable keyboard mapping */
	raw();
	scrollok(stdscr, TRUE);
	char input[2048];
	int i = 0;
	start_color();
	init_pair(1, COLOR_GREEN, COLOR_BLACK);
	init_pair(2, COLOR_BLACK, COLOR_WHITE);
	init_pair(3, COLOR_WHITE, COLOR_BLACK);

	while(i < 2047) {
		input[i] = getch();

		if (input[i] == 3) { // ctrl c
			endwin();
			exit(1);
		}

		if (input[i] == 7) { // ctrl g
			attron(COLOR_PAIR(1));
			printw("%s\n", "this should be green");
		}

		if (input[i] == 23) { // ctrl w
			attron(COLOR_PAIR(3));
		}

		if (input[i] == 11) { // ctrl k
			attron(COLOR_PAIR(2));
		}

		else if (input[i] == 7) { // if backspace
			delch();
			input[i]=' ';
			if (i>0) {
				i--;
			}
		}

		else {
			bzero(input, 2048);
		}
	}
}