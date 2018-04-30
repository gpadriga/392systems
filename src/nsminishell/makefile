CC = gcc
OBJS = nsminishell.o
CFLAGS = -Wall -Werror --pedantic -I../../include

all: $(OBJS)
	make -C../../src/my
	gcc $(OBJS) -o nsminishell -I../../include -L../../lib -llist -lmy -lncurses

clean:
	rm -f $(OBJS) 

fclean: clean
	rm -f nsminishell

re: fclean all