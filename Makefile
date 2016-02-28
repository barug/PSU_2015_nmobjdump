##
## Makefile for PSU_2015_nmobjdump in /home/barthe_g/rendu/tek2/unix_memoire/PSU_2015_nmobjdump
## 
## Made by Barthelemy Gouby
## Login   <barthe_g@epitech.net>
## 
## Started on  Tue Feb 16 09:43:25 2016 Barthelemy Gouby
## Last update Sun Feb 28 22:03:39 2016 Barthelemy Gouby
##

CC	= gcc

RM	= rm -f 

NAME1	= my_nm

NAME2	= my_objdump

SRCS1	= nm_process_file.c		\
	  nm_symbol_types.c		\
	  nm_symbol_types2.c		\
	  nm_symbol_types3.c		\
	  misc.c			\
	  main_nm.c

SRCS2	= objdump_process_file.c	\
	  objdump_architecture.c	\
	  misc.c			\
	  main_objdump.c

OBJS1	= $(SRCS1:.c=.o)

OBJS2	= $(SRCS2:.c=.o)

CFLAGS 	= -Wall -Werror -Wextra

.PHONY: nm objdump all clean fclean re

all: nm objdump

nm: $(OBJS1)
	$(CC) -o $(NAME1) $(OBJS1) $(CFLAGS)

objdump: $(OBJS2)
	$(CC) -o $(NAME2) $(OBJS2) $(CFLAGS)

clean:
	 $(RM) $(OBJS1) $(OBJS2)

fclean: clean
	$(RM) $(NAME1) $(NAME2)

re: fclean all
