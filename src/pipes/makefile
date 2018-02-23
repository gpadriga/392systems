# Makefile for pipes assignment
# Created on 2/23/2018
# Created by Jordan Tantuico
# Last changed on 2/23/2018
CC = gcc
OBJS = pipes.o 
CFLAGS = -Wall -Werror --pedantic -I../../include

all: $(OBJS)
	make -C../my all
	gcc $(OBJS) -o pipes -I../../include -L../../lib -lmy

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f pipes

re: fclean all