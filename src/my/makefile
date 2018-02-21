CFILES=my_strrindex.c my_strlen.c my_strindex.c my_str.c my_revstr.c \
my_num_base.c my_int.c my_digits.c my_char.c my_alpha.c my_strcat.c my_atoi.c \
my_strnconcat.c my_strdup.c my_strconcat.c my_strrfind.c my_strncpy.c \
my_strncmp.c my_strfind.c my_strcpy.c my_strcmp.c
OBJS=my_strrindex.o my_strlen.o my_strindex.o my_str.o my_revstr.o \
my_num_base.o my_int.o my_digits.o my_char.o my_alpha.o my_strcat.o my_atoi.o \
my_strnconcat.o my_strdup.o my_strconcat.o my_strcpy.o my_strncpy.o \
my_strfind.o my_strrfind.o my_strcmp.o my_strncmp.o
CFLAGS=-Wall -Werror --pedantic -std=c99 -Iinclude

all: 
	gcc -c -I../../include $(CFILES) $(CFLAGS)
	ar -rc libmy.a $(OBJS)
	ranlib libmy.a 
	mv libmy.a ../../lib

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f ../../lib/libmy.a

re: fclean all