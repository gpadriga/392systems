#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <signal.h>

static int intR = 0;

void sigStpHandler(int sig) {
	kill(0, SIGUSR1);
}

void sigIntHandler(int sig) {
	intR = 1;
	kill(0, SIGUSR2);
}

void rec1(int sig) {
	printf("%s\n", "Signal Received!");
}

void rec2(int sig) {
	printf("%s\n", "Child exiting...");
}

int main() {
	pid_t pid;
	if ( (pid = fork()) < 0) {
		perror("Child fork didn't work\n"), exit(1);
		return 1;
	} else if (pid == 0) { // child process
		signal(SIGINT, NULL);
		signal(SIGTSTP, NULL);
		signal(SIGUSR1, rec1);
		pause();
		signal(SIGUSR2, rec2);
		exit(0);
	}
	else { // parent 
		signal(SIGTSTP, sigStpHandler);
		pause();
		while (intR == 0);
		signal(SIGINT, sigIntHandler);
		wait(NULL); // wait for child to kill itself
		printf("%s\n", "Goodbye!");
		exit(0);
	}
}