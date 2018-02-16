#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>

int main() {
	pid_t pid;
	int fds[2];
	pipe(fds);

	if ( (pid = fork()) < 0) {
		perror("fork"), exit(1);
	} else if (pid == 0) {
		pid = getpid;
		close(fds[1]); //prevents writing
		char buf[500];
		read(fds[0], buf, 500);
		printf("%s", buf);
		printf("%s", "in child");
	} else {
		printf("%s", "in parent: child pid is ");
		printf("%d", pid);
		close(fds[0]); // prevents reading don't want 2 way pipe
		write(fds[1], "hello", 6);
		close(fds[1]);
		wait(NULL); // waits for any and all child process to finish
	}
	
	return 0;
}