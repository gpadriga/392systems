#include <stdlib.h>
#include <ncurses.h>
#include <string.h>
#include <math.h>
#include "my.h"

int row = 0, col=0, sel = 1, maxLen = 0;
int curStrLen, colNum=1, rowNum = 1;


void print(int argc, char * argv[], int highlights[]) {
	int colNum = col/(maxLen+1); // number of columns that can fit onscreen
	rowNum = (int)ceil((double)(argc-1)/(double)colNum);
	// no fit print
	if (col < maxLen || rowNum > row) {
		erase(); // clear what was there
		printw("please enlarge the window\n");
	}

	// it fit so print
	else {
		start_color();
		init_pair(1, COLOR_WHITE, COLOR_YELLOW);
		erase();
		int colIndex = 0;
		for (int i = 1; i < argc; i++) { // print everything in argv
			if (colIndex >= colNum) { 
				// go to next line
				printw("\n");
				colIndex = 0;
			}
			if (highlights[i] == 1) {
				start_color();
				attron(COLOR_PAIR(1));
			}
			if (i == sel) {
				attron(A_UNDERLINE);
			}
			printw("%s", argv[i]);
			curStrLen = strlen(argv[i]);
			attroff(A_UNDERLINE);
			attroff(COLOR_PAIR(1));
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
	noecho();
	scrollok(stdscr, FALSE);
	int input;

	// Array to store values that are highlighted
	int highlights[argc];
	for (int i = 0; i < argc; i++) {
		highlights[i] = 0;
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
			print(argc, argv, highlights);
		}

		if (someDone == 0) { // no resizing done
			input = getch();

			if (input == 27) { // esc
				endwin();
				exit(1);
			}

			colNum = col/(maxLen+1);

			if (input == KEY_UP) { // up
				if (sel > colNum) { // not in first row
					sel -= colNum;
				}
				else { // in first row
					while (sel + colNum < argc) {
						sel += colNum;
					}
				}
				print(argc, argv, highlights);
			}

			else if (input == KEY_DOWN) { // down
				if (sel + colNum < argc) { // not in last row
					sel += colNum;
				}
				else { // in the last row
					while (sel > colNum) {
						sel -= colNum;
					}
				}
				print(argc, argv, highlights);
			}

			else if (input == KEY_LEFT) { // left
				if (colNum > 1 && sel > 1 && (!(sel % colNum == 1))) { //not on extreme left
					sel--;
					print(argc, argv, highlights);
				}
			}

			else if (input == KEY_RIGHT) { // right
				if (!(sel % colNum == 0) && sel < argc-1) {
					sel++;
					print(argc, argv, highlights);
				}
			}
			else if (input == 32) { // space bar
				if (highlights[sel] == 0) { // not highlighted
					highlights[sel] = 1;
					if (sel < argc-1) {
						sel++;
					}
					else {
						sel = 1; // jump to first
					}
				}
				else { // is highlighted
					highlights[sel] = 0;
				}
				print(argc, argv, highlights);
			}

			else if (input == 10) { // enter
				endwin();
				for (int j = 0; j<argc; j++) {
					if (highlights[j] == 1) {
						my_str(argv[j]);
						my_str(" ");
					}
				}
				my_str("\n");
				exit(1);
			}

			else {

			}
		}
	}
}