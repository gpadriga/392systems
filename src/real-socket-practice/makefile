CC = gcc
OBJS = client.o server.o
CFLAGS = -Wall -Werror --pedantic

all: $(OBJS)
	gcc server.o -o server
	gcc client.o -o client

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f server client

re: fclean all