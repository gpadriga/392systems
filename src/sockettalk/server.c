#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h> 
#include "list.h"

// Usage: ./server [port]
int main(int argc, char *argv[]) {
	if (argc != 2) {
		perror("Usage: ./server [port]");
		exit(1);
	}
	// struct for list of users

}