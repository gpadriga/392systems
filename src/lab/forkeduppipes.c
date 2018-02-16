#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <string.h>

int my_strlen(char* c) {
  if (!c) {
    return -1;
  }
  int res = 0;
  while (*c != '\0') {
    res++;
    c++;
  }
  return res;
}

int my_revstr(char * c) {
	int len = my_strlen(c);
	if (len > 1) {
		for (int j = 0, half = len/2; j<= half; j++) {
			char temp = c[j];
			c[j] = c[len - 1 - j];
			c[len - 1 - j] = temp;
		}
	}
	return len;
}

int main() {
	pid_t pid;
	int parent[2];
	int child[2];
	pipe(parent);
	pipe(child);

	if ( (pid = fork()) < 0) {
		perror("fork didnt work"), exit(1);
	} else if (pid == 0) { // child
		char in[32] = "";
		while (read(parent[0], in, 32) > 0) {
			if (strncmp(in, "exit", 4) == 0) {
				break;
			}
			my_revstr(in);
			write(child[1], in, 32);
			char in[32] = "\0"; // clear in
		}
		exit(0);
	} else { // parent
		//close(fds[0]); // prevents reading don't want 2 way pipe
		char buffer[32] = "";
		char readin[32] = "";
		while (read(0, buffer, 32) > 0) {
			//printf("in parent:%s\n", buffer);
			if (strncmp(buffer, "exit", 4) == 0) {
				break;
			}
			write(parent[1], buffer, 32);
			char buffer[32] = "";
			read(child[0], readin, 32);
			//printf("in child:%s\n", readin);
			printf("%s\n", readin);
			char readin[32]= "\0";
		}
		write(parent[1], "exit", 5);
		wait(NULL); // waits for any and all child process to finish
		exit(0);
	}
	return 0;
}