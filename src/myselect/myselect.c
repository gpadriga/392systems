#include <stdlib.h>
#include <ncurses.h>
#include <string.h>

int row = 0, col=0, sel = 1, maxLen = 0;
int curStrLen, colNum=1;

void print(int argc, char * argv[]) {
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
			if (i == sel) {
				attron(A_UNDERLINE);
			}
			printw("%s", argv[i]);
			curStrLen = strlen(argv[i]);
			attroff(A_UNDERLINE);
			printw(" ");
			if (curStrLen < maxLen) { // pad spaces
				for (int j = 0; j < (maxLen - curStrLen); j++) {
					printw(" ");
				}
			}
			colIndex++;

		}
	}
}

int main(int argc, char *argv[]) {
	// list of files is from argv[1] on
	initscr();
	keypad(stdscr, TRUE);
	raw();
	char input;

	if (argc < 2) {
		// look @ dylans ques
	}

	// find size of longest filename
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
			print(argc, argv);
		}

		if (someDone == 0) { // no resizing done
			input = getch();

			if (input == 27) {
				endwin();
				exit(1);
			}

			colNum = col/(maxLen+1);

			if (input == 3) { // up
				if (sel > colNum) { // not in first row
					sel -= colNum;
				}
				else { // in first row
					if (sel + colNum < argc) {
						sel += colNum;
					}
				}
				print(argc, argv);
			}

			else if (input == 2) { // down
				if (sel < argc-1 - colNum) { // not in last row
					sel -= colNum;
				}
				else {
					sel = (argc - 1 - sel + colNum);
				}
				print(argc, argv);
			}

			else if (input == 4) { // left
				if (sel > 1 && (!(sel % colNum == 1))) { //not on extreme left
					sel--;
					print(argc, argv);
				}
			}

			else if (input == 5) { // right
				if (!(sel % colNum == 0) && sel < argc-1) {
					sel++;
					print(argc, argv);
				}
			}
		}
	}
}