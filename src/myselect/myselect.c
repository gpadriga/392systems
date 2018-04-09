#include <stdlib.h>
#include <ncurses.h>
#include <string.h>

int main(int argc, char *argv[]) {
	// list of files is from argv[1] on
	initscr();
	keypad(stdscr, TRUE);
	raw();
	char input;
	int curStrLen;
	int row=0, col=0;

	if (argc < 2) {
		// look @ dylans ques
	}

	// find size of longest filename
	int maxLen = 0;
	for (int i = 1; i<argc; i++) {
		int curLen = strlen(argv[i]);
		if (curLen > maxLen) {
			maxLen = curLen;
		}
	}

	while(1) {
		int someDone = 0;
		int oldCol = col;
		getmaxyx(stdscr, row, col);

		if (oldCol != col) { // changed since last print
			someDone = 1; // gonna do something

			// no fit print
			if (col < maxLen) {
				row=row; // I'm bad and I should feel bad
				erase(); // clear what was there
				printw("please enlarge the window\n");
			}

			// it fit so print
			else {
				erase();
				int colNum = col/(maxLen+1); // number of columns that can fit onscreen
				int colIndex = 0;
				for (int i = 1; i < argc; i++) { // print everything in argv
					if (colIndex >= colNum) { 
						// go to next line
						printw("\n");
						colIndex = 0;
					}
					printw("%s ", argv[i]);
					curStrLen = strlen(argv[i]);
					if (curStrLen < maxLen) { // pad spaces
						for (int j = 0; j < (maxLen - curStrLen); j++) {
							printw(" ");
						}
					}
					colIndex++;

				}
			}
		}

		if (someDone == 0) { // no resizing done
			input = getch();

			if (input == 27) { // escape case
				endwin();
				exit(1);
			}

		}
	}
}