CC = gcc
OBJS = minishell.o
CFLAGS = -Wall -Werror --pedantic -I../../include

all: $(OBJS)
	make -C../../src/my
	gcc $(OBJS) -o minishell -I../../include -L../../lib -lmy

clean:
	rm -f $(OBJS) 

fclean: clean
	rm -f minishell

re: fclean all