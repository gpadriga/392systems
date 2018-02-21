CC = gcc
OBJS = testList.o 
CFLAGS = -Wall -Werror --pedantic -I../../include

all: $(OBJS)
	make -C../../src/list
	gcc $(OBJS) -o test -I../../include -L../../lib -llist -lmy

clean:
	rm -f $(OBJS) 

fclean: clean
	rm -f test 

re: fclean all