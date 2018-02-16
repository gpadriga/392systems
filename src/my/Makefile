OBJS=lib.o my_char.o my_str.o my_int.o my_num_base.o my_alpha.o my_digits.o my_strlen.o my_revstr.o my_strindex.o my_strrindex.o my_strfind.o my_strrfrind.o my_strcmp.o my_strncmp.o my_strcpy.o my_strncpy.o my_strcat.o my_strdup.o my_strconcat.o my_strnconcat.o my_atoi.o
CFLAGS=-Wall -Werror --pedantic -std=c99 -Iinclude

all: $(OBJS)
    gcc $(OBJS) -o exec $(CFLAGS)
clean:
    rm -f $(OBJS)

fclean: clean
    rm -f exec

re: fclean all