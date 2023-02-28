##
## EPITECH PROJECT, 2021
## Project Name
## File description:
## my Makefile
##

SRCNM	=	src/nm/init_delete.c 	\

OBJNM	=	$(SRCNM:.c=.o)

MAINNM	=	nm.c

PLACE	=	lib/

LDFLAGS	=	-L lib/ -lmy

CPPFLAGS	=	-I ./include

CFLAGS	=	-Wall -Wextra

NAMENM	=	my_nm

all:	$(NAMENM)

nm:	$(NAMENM)

$(NAMENM):	makelib $(OBJNM)
	gcc $(MAINNM) $(SRCNM) $(MY) -o $(NAMENM) $(LDFLAGS) $(CPPFLAGS) $(CFLAGS)

makelib:
	$(MAKE) -C $(PLACE)

clean:
	rm -rf *~
	rm -rf $(OBJNM)

fclean: clean
	rm $(NAMENM)
	rm -rf *.a
	$(MAKE) -C $(PLACE) fclean

re: fclean makelib all

unitest: CFLAGS += -lcriterion
unitest:
	gcc -o $(NAMENM) $(CPPFLAGS) $(LDFLAGS) $(CFLAGS)

debug: CFLAGS += -g3
debug: all

.PHONY: all makelib clean fclean re unitest debug
