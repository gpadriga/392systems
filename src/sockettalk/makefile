CC = gcc
OBJS = client.o server.o
CFLAGS = -Wall -Werror --pedantic -I../../include

all: $(OBJS)
	make -C../list
	gcc server.o -o server -I ../../include -L../../lib -llist -lmy
	gcc client.o -o client -I ../../include -L../../lib -llist -lmy

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f server client

re: fclean all