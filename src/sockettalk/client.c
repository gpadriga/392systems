#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h> 
#include "my.h"
#include <signal.h>

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

    char cbuffer[2050];
    char pbuffer[1024];
    if (argc < 3) {
       my_str("Usage: ./client [hostname] [portno]\n");
       exit(0);
    }
    portno = atoi(argv[2]);
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) 
        perror("ERROR opening socket");
    server = gethostbyname(argv[1]);
    if (server == NULL) {
        perror("ERROR, no such host\n");
        exit(0);
    }
    bzero((char *) &serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    bcopy((char *)server->h_addr, 
         (char *)&serv_addr.sin_addr.s_addr,
         server->h_length);
    serv_addr.sin_port = htons(portno);
    if (connect(sockfd,(struct sockaddr *) &serv_addr,sizeof(serv_addr)) < 0) 
        perror("ERROR connecting");

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
        perror("ERROR writing username to socket");

    if ( (pid = fork()) < 0) {
        perror("Child fork didn't work\n"), exit(1);
        return 1;

    } else if (pid == 0) { // child listens and writes to terminal
        bzero(cbuffer, 2050);
        while(1) { // while reading is
            n = read(sockfd,cbuffer, 2049);
            if (n < 0) {
                perror("ERROR reading from socket");
                break;
            }
            my_str(cbuffer);
            bzero(cbuffer, 2050);
        }
    }
    else { // parent writes terminal input to server
        while (1) { // while your child is alive
            bzero(pbuffer, 1024);
            fgets(pbuffer, 1023, stdin);
            n = write(sockfd, pbuffer,strlen(pbuffer));
            if (n < 0) 
                 perror("ERROR writing to server");
            if (my_strcmp("/exit\n", pbuffer) == 0) {
                close(sockfd);
                kill(0, SIGKILL);
                exit(0);
            }
            bzero(pbuffer, 1024);
        }
    }
}
