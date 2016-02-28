/*
** nm_symbol_types.c for nm in /home/barthe_g/rendu/tek2/unix_memoire/PSU_2015_nmobjdump
** 
** Made by Barthelemy Gouby
** Login   <barthe_g@epitech.net>
** 
** Started on  Thu Feb 18 12:23:57 2016 Barthelemy Gouby
** Last update Fri Feb 26 18:50:06 2016 Barthelemy Gouby
*/

#include "nm_ressources.h"

char		get_symbol_type(Elf64_Sym *sym, t_sym_info *sym_info)
{
  char		(*test_funcs[11])(Elf64_Sym *sym_struct,
				  Elf64_Shdr *shdr) = {test_unique,
						       test_unspecific_weak,
						       test_weak,
						       test_undef,
						       test_absolute,
						       test_common,
						       test_uninitialized,
						       test_readonly,
						       test_initialized,
						       test_text,
						       NULL};
  int		i;

  i = 0;
  while (test_funcs[i] != NULL)
    {
      if (test_funcs[i](sym, sym_info->shdr) != 0)
	return (test_funcs[i](sym, sym_info->shdr));
      i++;
    }
  return ('?');
}
