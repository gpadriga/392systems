#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h> 
#include "my.h"

void error(const char *msg)
{
    perror(msg);
    exit(0);
}

int main(int argc, char *argv[])
{
    int sockfd, portno, n;
    struct sockaddr_in serv_addr;
    struct hostent *server;
    pid_t pid;

    char cbuffer[1024];
    char pbuffer[1024];
    if (argc < 3) {
       fprintf(stderr,"usage %s hostname port\n", argv[0]);
       exit(0);
    }
    portno = atoi(argv[2]);
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) 
        error("ERROR opening socket");
    server = gethostbyname(argv[1]);
    if (server == NULL) {
        fprintf(stderr,"ERROR, no such host\n");
        exit(0);
    }
    bzero((char *) &serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    bcopy((char *)server->h_addr, 
         (char *)&serv_addr.sin_addr.s_addr,
         server->h_length);
    serv_addr.sin_port = htons(portno);
    if (connect(sockfd,(struct sockaddr *) &serv_addr,sizeof(serv_addr)) < 0) 
        error("ERROR connecting");

     // Prompts the user for a username
    char username[1024];
    int isValid = 0;
    // Username cannot be empty
    while(isValid == 0) {
        my_str("Please enter a username: ");
        bzero(username, 1024);
        read(0, username, 1023);
        // Compress all the white space in a username
        my_rmws(username);
        if (my_strlen(username) == 0) {
            isValid = 0;
            my_str("Your username is invalid.\n");
        }
        else {
            isValid = 1;
        }
    }

    // before any messaging we need to send username
    n = write(sockfd, username,strlen(username));
    if (n < 0) 
        error("ERROR writing username to socket");

    if ( (pid = fork()) < 0) {
        perror("Child fork didn't work\n"), exit(1);
        return 1;
    } else if (pid == 0) { // child listens and writes to terminal
        while(1) {
            bzero(cbuffer, 1024);
            n = read(sockfd,cbuffer, 1023);
            if (n < 0) 
                 error("ERROR reading from socket");
            printf("%s", cbuffer);
        }
    }
    else { // parent writes terminal input to server
        while(1) {
            bzero(pbuffer, 1024);
            fgets(pbuffer, 1023, stdin);
            n = write(sockfd, pbuffer,strlen(pbuffer));
            if (n < 0) 
                 error("ERROR writing to socket");
        }
    }
    close(sockfd);
    return 0;
}
