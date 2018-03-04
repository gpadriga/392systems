CC = gcc
OBJS = test_mystr2vect.o 
CFLAGS = -Wall -Werror --pedantic -I../../include

all: $(OBJS)
	make -C../../src/my
	gcc $(OBJS) -o test -I../../include -L../../lib -lmy

clean:
	rm -f $(OBJS) 

fclean: clean
	rm -f test 

re: fclean all