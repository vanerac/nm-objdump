##
## EPITECH PROJECT, 2019
## base_repo
## File description:
## Makefile file
##

SRC		=		tools/tools.c
OBJ		=		$(SRC:%.c=%.o)


NM_MAIN			=		nm/main.c
ONM_MAIN		=		$(NM_MAIN:%.c=%.o)

OBJDUMP_MAIN	=		objdump/main.c
OOBJDUMP_MAIN	=		$(OBJDUMP_MAIN:%.c=%.o)

CFLAGS	=		-Iinclude/ -Wall -Wextra

NM		=		my_nm
OBJDUMP	=		my_objdump


all:	$(NM) $(OBJDUMP)

$(NM): $(OBJ) $(ONM_MAIN)
	gcc -o $(NM) $(OBJ) $(ONM_MAIN) $(CFLAGS)

$(OBJDUMP): $(OBJ) $(OOBJDUMP_MAIN)
	gcc -o $(OBJDUMP) $(OBJ) $(OOBJDUMP_MAIN) $(CFLAGS)

clean:
	rm -rf $(OBJ)
	rm -rf $(OTRC)
	rm -rf $(OMAIN)
	rm -rf $(OBJDUMP)
	rm -rf $(NM)
	rm -rf $(OOBJDUMP_MAIN)
	rm -rf $(ONM_MAIN)

fclean:	clean
	rm -rf unit_test

gclean:	fclean clean
	find . -name "*.gc*" -delete

re: gclean all


.PHONY:			gclean clean fclean re tests_run all
