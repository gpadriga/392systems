#include <stdlib.h>
#include <ncurses.h>
#include <strings.h>

// gcc c.c -lncurses -o cnc

int main() {
	//clear screen
	initscr();
	keypad(stdscr, TRUE);   /* enable keyboard mapping */
	raw();
	scrollok(stdscr, TRUE);

	char input[2048];
	int i = 0;

	while(i < 2047) {
		input[i] = getch();
		printw("%c", input[i]);
		if (input[i] == 23) {
			endwin();
			exit(1);
		}

		// enter text then hit down key
		else if (input[i] == 2) {
			beep();
			input[i] = '\n';
			printw("\n");
			start_color();
			init_pair(1, COLOR_RED, COLOR_BLACK); // red on blk
			attron(COLOR_PAIR(1));
			printw("%s", input);
			attroff(COLOR_PAIR(1));
			bzero(input, 2048);
			i = 0;
		}

		else if (input[i] == 7) { // if backspace
			delch();
			input[i]=' ';
			if (i>0) {
				i--;
			}
		}

		else {
			i++;
		}
	}
}

/**
	2 point: initialize ncurses (clear terminal screen), exit echo terminal on ctrl + w,
	and restore the original command terminal
	DONE

	3 points: Allow user to enter text, spit back out text on next line, and re-allow
	user to enter text, and scroll when reach bottom of window

	2 points: Print responses in red

	6 points: implement backspace button

	Max points: 13
**/