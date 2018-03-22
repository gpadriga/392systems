#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h> 

void error(char *msg)
{
  perror("something hecked up");
  exit(0);
}

// ./client <host> <port> <message>
int main(int argc, char *argv[]) {
	if (argc != 4) {
		printf("%s\n", "That's not how u use this");
		exit(0);
	}
	int sockfd, portno, n;
  	struct sockaddr_in serv_addr;
 	struct hostent *server;

 	char buffer[256];
 	portno = atoi(argv[2]);
	sockfd = socket(AF_INET, SOCK_DGRAM, 0);
	if (sockfd < 0) {
  		error("ERROR opening socket");
  	}
  	server = gethostbyname(argv[1]);
	if (server == NULL) {
		  fprintf(stderr,"ERROR, no such host");
		  exit(0);
	}
	bzero((char *) &serv_addr, sizeof(serv_addr));
	serv_addr.sin_family = AF_INET;
	bcopy((char *)server->h_addr,
	      (char *)&serv_addr.sin_addr.s_addr,
	      server->h_length);
	serv_addr.sin_port = htons(portno);
	if (connect(sockfd,&serv_addr,sizeof(serv_addr)) < 0) {
		error("ERROR connecting");
	}
	// send to server
	n = write(sockfd,argv[3],strlen(argv[3]));
	if (n < 0) {
		error("ERROR writing to socket");
	}
	// read first time
	bzero(buffer,256);
	n = read(sockfd,buffer,255);
	if (n < 0) {
		error("ERROR reading from socket");
	}
	printf("%s\n",buffer);
	// read second time
	bzero(buffer,256);
	n = read(sockfd,buffer,255);
	if (n < 0) {
		error("ERROR reading from socket");
	}
	printf("%s\n",buffer);
	close(sockfd);
	return 0;
}