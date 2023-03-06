##
## EPITECH PROJECT, 2021
## Project Name
## File description:
## my Makefile
##

SRCNM	=	src/nm/nm_64/init_delete.c 	\
			src/nm/nm_64/nm_64.c \
			src/nm/nm_64/sec_symtab.c \
			src/nm/nm_64/print_type.c \
			src/nm/nm_32/init_delete.c 	\
			src/nm/nm_32/nm_32.c \
			src/nm/nm_32/sec_symtab.c \
			src/nm/nm_32/print_type.c \
			src/nm/start_nm.c \

OBJNM	=	$(SRCNM:.c=.o)

SRCOBJ	=	src/obj/start_obj.c \
			src/obj/obj_64/obj_64.c \
			src/obj/obj_32/obj_32.c \
			src/nm/nm_64/init_delete.c 	\
			src/nm/nm_32/init_delete.c 	\

OBJOBJ	=	$(SRCOBJ:.c=.o)

MAINNM	=	nm.c

MAINOBJ	=	obj.c

PLACE	=	lib/

LDFLAGS	=	-L lib/ -lmy

CPPFLAGS	=	-I ./include

CFLAGS	=	-Wall -Wextra

NAMENM	=	my_nm

NAMEOBJ	=	my_objdump

all:	nm objdump

nm:	makelib $(OBJNM)
	gcc $(MAINNM) $(SRCNM) $(MY) -o $(NAMENM) $(LDFLAGS) $(CPPFLAGS) $(CFLAGS)

objdump:	makelib $(OBJOBJ)
	gcc $(MAINOBJ) $(SRCOBJ) $(MY) -o $(NAMEOBJ) $(LDFLAGS) \
	$(CPPFLAGS) $(CFLAGS)

makelib:
	$(MAKE) -C $(PLACE)

clean:
	rm -rf *~
	rm -rf $(OBJNM)
	rm -rf $(OBJOBJ)

fclean: clean
	rm -rf $(NAMENM)
	rm -rf $(NAMEOBJ)
	rm -rf *.a
	$(MAKE) -C $(PLACE) fclean

re: fclean makelib all

unitest: CFLAGS += -lcriterion
unitest:
	gcc -o $(NAMENM) $(CPPFLAGS) $(LDFLAGS) $(CFLAGS)

debug: CFLAGS += -g3
debug: all

.PHONY: all makelib clean fclean re unitest debug
