/*
** nm_symbol_types2.c for nmobjdump in /home/barthe_g/rendu/tek2/unix_memoire/PSU_2015_nmobjdump
** 
** Made by Barthelemy Gouby
** Login   <barthe_g@epitech.net>
** 
** Started on  Fri Feb 26 17:49:11 2016 Barthelemy Gouby
** Last update Fri Feb 26 17:55:30 2016 Barthelemy Gouby
*/

#include "nm_ressources.h"

char		test_unique(Elf64_Sym *sym, Elf64_Shdr *shdr)
{
  (void) shdr;
  return (ELF64_ST_BIND(sym->st_info) == STB_GNU_UNIQUE ? 'c' : 0);
}

char		test_unspecific_weak(Elf64_Sym *sym, Elf64_Shdr *shdr)
{
  (void) shdr;
  if (ELF64_ST_BIND(sym->st_info) == STB_WEAK)
    {
      return ('W');
      if (sym->st_shndx == SHN_UNDEF)
        return ('w');
    }
  return (0);
}

char		test_weak(Elf64_Sym *sym, Elf64_Shdr *shdr)
{
  (void) shdr;
  if (ELF64_ST_BIND(sym->st_info) == STB_WEAK &&
      ELF64_ST_TYPE(sym->st_info) == STT_OBJECT)
    {
      return ('V');
      if (sym->st_shndx == SHN_UNDEF)
	return ('v');
    }
  return (0);
}

char		test_undef(Elf64_Sym *sym, Elf64_Shdr *shdr)
{
  (void) shdr;
  return (sym->st_shndx == SHN_UNDEF ? 'U' : 0);
}

char		test_absolute(Elf64_Sym *sym, Elf64_Shdr *shdr)
{
  (void) shdr;
  return (sym->st_shndx == SHN_ABS ? 'A' : 0);
}
