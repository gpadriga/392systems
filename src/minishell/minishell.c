#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include "my.h"

/* Things that may be useful:
	int chdir (const char *path) : changes current working directory
	char* get_current_dir_name(void) : self explanatory, for debugging
	int execvp (const char *file, char *const argv[]) : created child
		process does not have to run the same program as the parent process
		does. The exec type system calls allow a process to run any program files,
		which include a binary executable or a shell script
		file: points to the file name associated with the file being executed.
		argv:  is a null terminated array of character pointers.
*/



int main() {
	while (1) {
		// print prompt and current working directory
		char cwd[1024];
		my_str("MINISHELL: ");
		my_str(getcwd(cwd, sizeof(cwd))); 
		my_str(" $: ");
		int buff = (10);
		char* input = malloc(buff*sizeof(char));
		int seen = 0;
		char* begin = input;
		read(0, input, 1);
		seen++;
		while (*input != '\n') {
			if (seen >= buff) {
				buff*=2;
				char * newInput;
				newInput = (char *) realloc(begin, buff*sizeof(char));
				begin = newInput;
			}
			input++;
			seen++;
			read(0, input, 1);
		}
		char ** dir = my_str2vect(begin);
		if (my_vectsize(dir) == 0) {
			my_str("Please enter something, type help if you don't know anything\n");
		}
		else if (my_strcmp(dir[0], "cd") == 0) {
			// try going to that dir using chdir
				// need to include support for .../
			// if unsuccessful
				// my_str("That directory doesn't exist");
			
		}
		else if (my_strcmp(dir[0], "ls") == 0 && my_vectsize(dir) == 1) {
			my_str("Not implemented yet");
		}
		else if (my_strcmp(dir[0], "help") == 0 && my_vectsize(dir) == 1) {
			my_str("lemme help u\n");
		}
		else if (my_strcmp(dir[0], "exit") == 0 && my_vectsize(dir) == 1) {
			my_str("That's all folks!\n");
			return 1;
		}
		else if (my_strcmp(dir[0], "./idunnoyet") == 0) {// I dunno how we're gonna implement this {
			//use execvp and str2vect to pass args
			// fork before execvp
			my_str("Not implemented yet");
		}
		else {
			my_str("What does that even mean dude?\n");
		}
	}
}
