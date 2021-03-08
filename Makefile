##
## EPITECH PROJECT, 2019
## base_repo
## File description:
## Makefile file
##

SRC		=		tools/tools.c

OBJ		=		$(SRC:%.c=%.o)

TRC		=		NULL

OTRC	=		$(TRC:.c=.o)


NM_MAIN			=		nm/main.c
ONM_MAIN		=		$(NM_MAIN=.o)

OBJDUMP_MAIN	=		objdump/main.c
OOBJDUMP_MAIN	=		$(OBJDUMP_MAIN=.o)

CFLAGS	=		-Iinclude/ -Wall -Wextra

NM		=		my_nm
OBJDUMP	=		my_objdump


all:	$(NM) $(OBJDUMP)

$(NM): $(OBJ) $(NM_MAIN)
	gcc -o $(NM) $(OBJ) $(NM_MAIN) $(CFLAGS)

$(OBJDUMP): $(OBJ) $(OBJDUMP_MAIN)
	gcc -o $(OBJDUMP) $(OBJ) $(OBJDUMP_MAIN) $(CFLAGS)

clean:
	rm -rf $(OBJ)
	rm -rf $(OTRC)
	rm -rf $(OMAIN)

fclean:	clean
	rm -rf $(NAME)
	rm -rf unit_test

gclean:	fclean clean
	find . -name "*.gc*" -delete

re: gclean all

tests_run:	$(OTRC) $(OBJ)
	gcc -o unit_test $(TRC) $(SRC) $(CFLAGS) -lcriterion --coverage
	./unit_test

.PHONY:			gclean clean fclean re tests_run all
