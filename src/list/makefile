CC = gcc
OBJS = new_node.o add_node.o add_node_at.o add_elem.o append.o \
count_s_nodes.o debug_string.o debug_char.o debug_int.o \
remove_last.o print_int.o print_char.o print_string.o \
remove_node.o add_elem.o empty_list.o remove_node_at.o \
traverse_char.o traverse_int.o traverse_string.o add_node_at.o \
node_at.o elem_at.o
CFLAGS = -Wall -Werror --pedantic -I../../include

all: $(OBJS)
	make -C ../my all
	ar -rc liblist.a $(OBJS)
	ranlib liblist.a 
	mv liblist.a ../../lib

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f ../../lib/liblist.a

re: fclean all