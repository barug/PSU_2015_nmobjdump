//
// nm_ressources.h for nm in /home/barthe_g/rendu/tek2/unix_memoire/PSU_2015_nmobjdump
// 
// Made by Barthelemy Gouby
// Login   <barthe_g@epitech.net>
// 
// Started on  Tue Feb 16 11:01:19 2016 Barthelemy Gouby
// Last update Thu Feb 18 12:12:46 2016 Barthelemy Gouby
//

#ifndef _MY_NM
# define _MY_NM

#define _GNU_SOURCE

#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <stdio.h>
#include <string.h>
#include <elf.h>
#include <ctype.h>

typedef struct	s_arguments
{
  char		**file_paths;
}		t_arguments;

typedef struct	s_sym_info
{
  char		*symbol_names;
  Elf64_Sym	*symbol_table;
  size_t	st_entry_size;
  size_t	st_size;
  size_t	st_length;
}		t_sym_info;

typedef struct	s_sym
{
  char		*name;
  uint64_t	value;
}		t_sym;

void		*open_file(char *file_path);
int		analyse_file_data(void	*data, t_arguments *arguments);


#endif /* !_MY_NM */
