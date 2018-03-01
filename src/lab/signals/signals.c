#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <signal.h>

static pid_t pid;
static int c = 0;
static int cTog = 0;

void sigStpHandler(int sig) {
	kill(pid, SIGUSR1);
	alarm(10);
}

void sigIntHandler(int sig) {
	kill(pid, SIGUSR2);
	cTog = 0? 1 : 0;
}

void alarmHandler(int sig) {
	printf("%s\n", "Time's up");
	exit(0);
}

void rec1(int sig) {
	printf("%s\n", "Signal Received!");
}

void rec2(int sig) {
	printf("%s\n", "Child exiting...");
	c = 1;
	exit(0);
}

void doNone(int sig) {

}

int main() {
	if ( (pid = fork()) < 0) {
		perror("Child fork didn't work\n"), exit(1);
		return 1;
	} else if (pid == 0) { // child process
		signal(SIGINT, doNone); // set SIGINT to do nothing
		signal(SIGTSTP, doNone); // set SIGTSTP to do nothing
		signal(SIGUSR1, rec1); // when SIGUSR1 recieved, print so
		signal(SIGUSR2, rec2);
		while (1) {
			pause(); // wait for next sig
		}
	}
	else { // parent 
		signal(SIGTSTP, sigStpHandler);
		signal(SIGALRM, alarmHandler);
		signal(SIGINT, sigIntHandler);
		signal(SIGUSR1, doNone);
		signal(SIGUSR2, doNone);
		while (1) {
			pause();
			wait(NULL); // wait for child to kill itself
			pause();
			if (c = 1 && cTog == 0) {
				printf("%s\n", "Goodbye!");
				exit(0);
			}	
		}
	}
	return 0;
}