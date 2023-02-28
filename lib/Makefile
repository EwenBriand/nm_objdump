##
## EPITECH PROJECT, 2021
## Makefile
## File description:
## Makefile
##

SRC	=	my_putchar.c	\
		my_putnbr.c	\
		my_putstr.c	\
		my_revstr.c	\
		my_strcat.c	\
		my_strlen.c	\
		my_strlen_int.c	\
		get_buffer.c	\
		make_word_array.c	\

ALLGCC	=	my_putchar.o	\
			my_putnbr.o	\
			my_putstr.o	\
			my_revstr.o	\
			my_strcat.o	\
			my_strlen.o	\
			my_strlen_int.o	\
			get_buffer.o	\
			make_word_array.o \

NAME	=	libmy.a

all:	obj libmaker clean

libmaker:
	ar rc $(NAME) $(ALLGCC)

obj:
	gcc -c $(SRC) -I ../include

clean:
	rm -f *.o
	rm -f *~

fclean:	clean
	rm -f *.a

.PHONY: all libmaker clean fclean obj
