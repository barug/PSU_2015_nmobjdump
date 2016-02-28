//
// nm_ressources.h for nm in /home/barthe_g/rendu/tek2/unix_memoire/PSU_2015_nmobjdump
// 
// Made by Barthelemy Gouby
// Login   <barthe_g@epitech.net>
// 
// Started on  Tue Feb 16 11:01:19 2016 Barthelemy Gouby
// Last update Fri Feb 26 18:54:13 2016 Barthelemy Gouby
//

#ifndef _MY_NM_
# define _MY_NM_

#define _GNU_SOURCE

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

typedef struct	s_sym_info
{
  Elf64_Shdr	*shdr;
  char		*symbol_names;
  Elf64_Sym	*symbol_table;
  size_t	st_entry_size;
  size_t	st_size;
  size_t	st_length;
}		t_sym_info;

typedef struct	s_sym_type_test
{
  int		(*test_type)(Elf64_Sym *sym);
  char		type_char;
}		t_sym_type_test;

int		analyse_file_data(void	*data, t_arguments *arguments);
char		get_symbol_type(Elf64_Sym *sym, t_sym_info *sym_info);
void		*open_file(char *file_path);
int		check_header_type(Elf64_Ehdr * data);
int		get_arguments(int argc, char **argv, t_arguments *arguments);

char		test_unique(Elf64_Sym *sym, Elf64_Shdr *shdr);
char		test_unspecific_weak(Elf64_Sym *sym, Elf64_Shdr *shdr);
char		test_weak(Elf64_Sym *sym, Elf64_Shdr *shdr);
char		test_undef(Elf64_Sym *sym, Elf64_Shdr *shdr);
char		test_absolute(Elf64_Sym *sym, Elf64_Shdr *shdr);
char		test_common(Elf64_Sym *sym, Elf64_Shdr *shdr);
char		test_uninitialized(Elf64_Sym *sym, Elf64_Shdr *shdr);
char		test_readonly(Elf64_Sym *sym, Elf64_Shdr *shdr);
char		test_initialized(Elf64_Sym *sym, Elf64_Shdr *shdr);
char		test_text(Elf64_Sym *sym, Elf64_Shdr *shdr);

#endif /* !_MY_NM_ */
