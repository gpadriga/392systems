# Makefile for my library
# Edited on 2/23/2018 to add support for pipes
CC = gcc
OBJS = my_strrindex.o my_strlen.o my_strindex.o my_str.o my_revstr.o \
my_num_base.o my_int.o my_digits.o my_char.o my_alpha.o my_strcat.o my_atoi.o \
my_strnconcat.o my_strdup.o my_strconcat.o my_strcpy.o my_strncpy.o \
my_strfind.o my_strrfind.o my_strcmp.o my_strncmp.o my_vect2str.o
CFLAGS = -Wall -Werror --pedantic -I../../include

all: $(OBJS)
	ar -rc libmy.a $(OBJS)
	ranlib libmy.a 
	mv libmy.a ../../lib

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f ../../lib/libmy.a

re: fclean all