#include <unistd.h>

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
	// change dir to home/username
	/*
	while (1) {
		// print prompt and current working directory
		given that command is the first arguement
		if (command) == "cd" {
			// try going to that dir using chdir
			// if unsuccessful
				// my_str("That directory doesn't exist");
			if successful
		}
		else if (command) == "ls" {
			
		}
		else if (command) == "help" {
		
		}
		else if (command) == "exit" {
			my_str("That's all folks!");
			return 1;
		}
		else if (command) == "./someprogram" // I dunno how we're gonna implement this {
			use execvp and str2vect to pass args
		}
		else {
			my_str("What does that even mean dude?")
		}
	}
	*/
}
