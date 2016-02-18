##
## Makefile for PSU_2015_nmobjdump in /home/barthe_g/rendu/tek2/unix_memoire/PSU_2015_nmobjdump
## 
## Made by Barthelemy Gouby
## Login   <barthe_g@epitech.net>
## 
## Started on  Tue Feb 16 09:43:25 2016 Barthelemy Gouby
## Last update Thu Feb 18 12:11:44 2016 Barthelemy Gouby
##

CC	= gcc

RM	= rm -f 

NAME1	= my_nm

NAME2	= my_objdump

SRCS1	= nm_process_file.c	\
	  main_nm.c

SRCS2	= main_obdump.c

OBJS1	= $(SRCS1:.c=.o)

OBJS2	= $(SRCS2:.c=.o)

CFLAGS 	= -Wall -Werror -Wextra

nm: $(OBJS1)
	$(CC) -o $(NAME1) $(OBJS1) $(CFLAGS)

objdump: $(OBJS2)
	$(CC) -o $(NAME2) $(OBJS2) $(CFLAGS)

all: nm objdump

clean: $(RM) $(OBJS1) $(OBJS2)

fclean: clean
	$(RM) $(NAME1) $(NAME2)

re: fclean all

.PHONY: nm objdump all clean fclean re
