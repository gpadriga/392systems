CC = gcc
OBJS = myselect.o
CFLAGS = -Wall -Werror --pedantic -I../../include -I/home/jbass/ncurses/include

all: $(OBJS)
	gcc myselect.o -o myselect -I../../include -L/home/jbass/ncurses/lib -L../../lib -lmy -lm -lncurses
	export TERMINFO=/lib/terminfo

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f myselect

re: fclean all