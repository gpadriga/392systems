CC = gcc
OBJS = myselect.o
CFLAGS = -Wall -Werror --pedantic -I../../include

all: $(OBJS)
	gcc myselect.o -lncurses -o myselect -I../../include -L../../lib -lmy 

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f ncurses

re: fclean all