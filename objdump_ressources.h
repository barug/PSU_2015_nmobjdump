//
// objdump_ressources.h for objdump in /home/barthe_g/rendu/tek2/unix_memoire/PSU_2015_nmobjdump
// 
// Made by Barthelemy Gouby
// Login   <barthe_g@epitech.net>
// 
// Started on  Thu Feb 18 15:15:43 2016 Barthelemy Gouby
// Last update Fri Feb 26 16:49:05 2016 Barthelemy Gouby
//

#ifndef _OBJDUMP
# define _OBJDUMP

#include <unistd.h>
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
  size_t	number_of_files;
}		t_arguments;

typedef struct	s_arch_type
{
  int		type;
  char*		type_name;
}		t_arch_type;

void		*open_file(char *file_path);
int		check_header_type(Elf64_Ehdr * data);
int		analyse_file_data(void	*data, t_arguments *arguments);
int		get_arguments(int argc, char **argv, t_arguments *arguments);

#endif /* !_OBJDUMP */
