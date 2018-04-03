#include <stdio.h>
#include <stdlib.h>
#include <sys/ioctl.h>
#include <sys/poll.h>
#include <sys/socket.h>
#include <sys/time.h>
#include <netinet/in.h>
#include <errno.h>
#include <unistd.h>
#include <string.h>
#include "list.h"

//#define SERVER_PORT  12345

#define TRUE             1
#define FALSE            0

int main (int argc, char *argv[])
{
  int    len, rc, on = 1;
  int    listen_sd = -1, new_sd = -1;
  int    end_server = FALSE;
  char   read[1024];
  char   bigboi[2050]; // 1024 + ": " + 1024
  struct sockaddr_in   addr;
  int    timeout;
  struct pollfd* fds = (struct pollfd*)malloc(sizeof(struct pollfd) * 10);
  struct s_node* server = new_node("server",NULL, NULL); // server name node
  struct s_node** lhead = &server; // ref to start of list
  int    fdsSize = 1;
  int    nfds = 1, current_size = 0, i, j;

  if (argc != 2) {
    perror("Usage: /server [portNo]");
    exit(1);
  }

  /*************************************************************/
  /* Create an AF_INET6 stream socket to receive incoming      */
  /* connections on                                            */
  /*************************************************************/
  listen_sd = socket(AF_INET, SOCK_STREAM, 0);
  if (listen_sd < 0)
  {
    perror("socket() failed");
    exit(-1);
  }

  /*************************************************************/
  /* Allow socket descriptor to be reuseable                   */
  /*************************************************************/
  rc = setsockopt(listen_sd, SOL_SOCKET,  SO_REUSEADDR,
                  (char *)&on, sizeof(on));
  if (rc < 0)
  {
    perror("setsockopt() failed");
    close(listen_sd);
    exit(-1);
  }

  /*************************************************************/
  /* Set socket to be nonblocking. All of the sockets for      */
  /* the incoming connections will also be nonblocking since   */
  /* they will inherit that state from the listening socket.   */
  /*************************************************************/
  rc = ioctl(listen_sd, FIONBIO, (char *)&on);
  if (rc < 0)
  {
    perror("ioctl() failed");
    close(listen_sd);
    exit(-1);
  }

  /*************************************************************/
  /* Bind the socket                                           */
  /*************************************************************/
  addr.sin_family      = AF_INET;
  addr.sin_addr.s_addr = INADDR_ANY;
  addr.sin_port        = htons(atoi(argv[1]));
  rc = bind(listen_sd,
            (struct sockaddr *)&addr, sizeof(addr));
  if (rc < 0)
  {
    perror("bind() failed");
    close(listen_sd);
    exit(-1);
  }

  /*************************************************************/
  /* Set the listen back log                                   */
  /*************************************************************/
  rc = listen(listen_sd, 32);
  if (rc < 0)
  {
    perror("listen() failed");
    close(listen_sd);
    exit(-1);
  }

  /*************************************************************/
  /* Initialize the pollfd structure                           */
  /*************************************************************/
  memset(fds, 0 , sizeof(*fds));

  /*************************************************************/
  /* Set up the initial listening socket                        */
  /*************************************************************/
  fds[0].fd = listen_sd;
  fds[0].events = POLLIN;
  /*************************************************************/
  /* Initialize the timeout to 3 minutes. If no                */
  /* activity after 3 minutes this program will end.           */
  /* timeout value is based on milliseconds.                   */
  /*************************************************************/
  timeout = -1;

  /*************************************************************/
  /* Loop waiting for incoming connects or for incoming data   */
  /* on any of the connected sockets.                          */
  /*************************************************************/
  do
  {
    /***********************************************************/
    /* Call poll() and wait 3 minutes for it to complete.      */
    /***********************************************************/
    my_str("Waiting on poll()...\n");
    rc = poll(fds, nfds, timeout);

    /***********************************************************/
    /* Check to see if the poll call failed.                   */
    /***********************************************************/
    if (rc < 0)
    {
      perror("  poll() failed");
      break;
    }

    /***********************************************************/
    /* One or more descriptors are readable.  Need to          */
    /* determine which ones they are.                          */
    /***********************************************************/
    current_size = nfds;
    for (i = 0; i < current_size; i++)
    {
      /*********************************************************/
      /* Loop through to find the descriptors that returned    */
      /* POLLIN and determine whether it's the listening       */
      /* or the active connection.                             */
      /*********************************************************/
      if(fds[i].revents == 0)
        continue; // nothing intersting on this fd

      if (fds[i].fd == listen_sd)
      {
        /*******************************************************/
        /* Listening descriptor is readable.                   */
        /*******************************************************/
        my_str("Listening socket is readable\n");

        /*******************************************************/
        /* Accept all incoming connections that are            */
        /* queued up on the listening socket before we         */
        /* loop back and call poll again.                      */
        /*******************************************************/
        do
        {
          /*****************************************************/
          /* Accept each incoming connection. If               */
          /* accept fails with EWOULDBLOCK, then we            */
          /* have accepted all of them. Any other              */
          /* failure on accept will cause us to end the        */
          /* server.                                           */
          /*****************************************************/
          new_sd = accept(listen_sd, NULL, NULL);
          if (new_sd < 0)
          {
            if (errno != EWOULDBLOCK)
            {
              perror("accept() failed");
            }
            break;
          }

          /*****************************************************/
          /* Add the new incoming connection to the            */
          /* pollfd structure                                  */
          /*****************************************************/
          my_str("New incoming connection");
          if (nfds+1 > fdsSize) {
            fdsSize *= 2;
            fds = (struct pollfd*) realloc(fds, fdsSize*sizeof(struct pollfd));
          }
          fds[nfds].fd = new_sd;
          fds[nfds].events = POLLIN;
          nfds++;

          // read username from newest connection
          bzero(read,1024);
          rc = recv(new_sd, read, sizeof(read), 0);
          if (rc < 0) {
            if (errno != EWOULDBLOCK) {
              perror("username recv() failed");
              //close_conn = TRUE;
            }
          }

          // Add the username to list of usernames
          char* name = my_strdup(read);
          struct s_node* username = new_node(name, NULL, NULL);
          print_string(username);
          append(username, lhead);

          /*****************************************************/
          /* Loop back up and accept another incoming          */
          /* connection                                        */
          /*****************************************************/
        } while (new_sd != -1);
      }

      /*********************************************************/
      /* This is not the listening socket, therefore an        */
      /* existing connection must be readable                  */
      /*********************************************************/

      else
      {
        my_str("Can read\n");

        /*****************************************************/
        /* Receive data on this connection until the         */
        /* recv fails with EWOULDBLOCK. If any other         */
        /* failure occurs, we will close the                 */
        /* connection.                                       */
        /*****************************************************/
        bzero(read,1024);
        rc = recv(fds[i].fd, read, 1024, 0);
        if (rc < 0)
        {
          if (errno != EWOULDBLOCK)
          {
            perror("  recv() failed");
          }
          break;
        }

        /*****************************************************/
        /* Data was received                                 */
        /*****************************************************/
        len = rc;
        printf("%d bytes received\n", len);

        /*****************************************************/
        /* Echo the data back to the clients                 */
        /*****************************************************/
        
        if (my_strncmp("/nick ", read, 6) == 0) { // change username
          //my_str("you're trying to change your username!\n");
          char *point = read;
          for (int i = 0; i<6; i++) {
            point++;
          }
          my_str(point); // here it points to the new UN
          my_rmws(point); 
          if (my_strlen(point) == 0) {
            send(fds[i].fd, "That username is invalid\n", 50, 0);
          }
          else {
            struct s_node* cur = node_at(*lhead, i);
            char* new_name = my_strdup(point);
            cur->elem = new_name;
          }
        }

        else if (my_strcmp("/exit\n", read) == 0) { // /exit case
          close(fds[i].fd);
          //remove from llist
          remove_node_at(lhead, i);
          // remove from fds
          fds[i].fd = -1;
          for (i = 0; i < nfds; i++)
          {
            if (fds[i].fd == -1)
            {
              for(j = i; j < nfds; j++)
              {
                fds[j].fd = fds[j+1].fd;
              }
              i--;
              nfds--;
            }
          }
        }

        else if (my_strncmp("/me ", read, 4) == 0) {
          char* un = (char *) elem_at(*lhead, i);
          bzero(bigboi, 2050);
          my_strcat(bigboi, un);
          // change read from "/me [text" -> [text]
          char *point = read;
          for (int i = 0; i<3; i++) {
            point++;
          }
          my_strcat(bigboi, point);
          for (int j=1;j<nfds;j++) {
            rc = send(fds[j].fd, bigboi, my_strlen(bigboi), 0);
            if (rc < 0)
            {
              perror("send() failed");
              break;
            }
          }
          bzero(bigboi, 2050);
        }

        else { // no special commands, just send as [un]: [message]
          // Get the username of the person sending the message
          char* un = (char *) elem_at(*lhead, i);
          bzero(bigboi, 2050);
          // Append the username, colon, space, and message in one string
          my_strcat(bigboi, un);
          my_strcat(bigboi, ": ");
          my_strcat(bigboi, read);

          for (int j=1;j<nfds;j++) {
            rc = send(fds[j].fd, bigboi, my_strlen(bigboi), 0);
            if (rc < 0)
            {
              perror("send() failed");
              break;
            }
          }
          bzero(bigboi, 2050);
        } // end of sending

      }  /* End of existing connection is readable             */
    } // End of fds loop

  } while (end_server == FALSE); /* End of serving running.    */

  /*************************************************************/
  /* Clean up all of the sockets that are open                 */
  /*************************************************************/
  for (i = 0; i < nfds; i++)
  {
    if(fds[i].fd >= 0)
      close(fds[i].fd);
  }
}


