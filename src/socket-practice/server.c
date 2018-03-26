/* A simple server in the internet domain using TCP
   The port number is passed as an argument */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h> 
#include <sys/socket.h>
#include <netinet/in.h>
#include "list.h"

void error(const char *msg)
{
    perror(msg);
    exit(1);
}

int main(int argc, char *argv[])
{
    int sockfd, newsockfd, portno;
    socklen_t clilen;
    char buffer[256];
    struct sockaddr_in serv_addr, cli_addr;
    int n;
    // Usage case
    if (argc < 2) {
        my_str("Arrrrgh! There was no port provided!\n");
        exit(1);
    }
    // Creates the socket
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) 
        error("Arrrrgh! There was an error opening the socket!");
    bzero((char *) &serv_addr, sizeof(serv_addr));
    portno = my_atoi(argv[1]);
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    serv_addr.sin_port = htons(portno);
    // Binds the socket to an address
    if (bind(sockfd, (struct sockaddr *) &serv_addr,
            sizeof(serv_addr)) < 0) 
            error("Arrrrgh! There was an error on binding!");
    // Listens for incoming connections
    listen(sockfd,5);
    clilen = sizeof(cli_addr);
    // Accepts the connection
    newsockfd = accept(sockfd, 
                (struct sockaddr *) &cli_addr, 
                &clilen);
    if (newsockfd < 0) 
        error("Arrrrgh! There was an error on accepting!");
    // Indicates new user has joined
    my_str("A new landlubber has hopped aboard!\n");

    // Sends welcome message
    bzero(buffer, 256);
    n = write(newsockfd,"Ahoy, matey! Welcome aboard the Flying Dutchman!",48);
    if (n < 0) error("Arrrrgh! There was an error writing!");

    // Endless messaging
    while(1) {
        bzero(buffer,256);
        // Reads a message from the client
        n = read(newsockfd,buffer,255);
        if (n < 0) error("Arrrrgh! There was an error from reading!");
        my_str("Thar be the message: ");
        my_str(buffer);
        // Sends a confirmation to the client
        char* send = my_strconcat("Here's yer message: ", buffer);
        n = write(newsockfd,send,my_strlen(send));
        free(send);
        if (n < 0) error("Arrrrgh! There was an error writing!");
    }

    // Sends farewell message
    bzero(buffer, 256);
    n = write(newsockfd,"It's time for ye to walk the plank!",35);
    if (n < 0) error("Arrrrgh! There was an error writing!");

    // Closes the connection
    close(newsockfd);
    close(sockfd);
    return 0; 
}
