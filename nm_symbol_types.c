/*
** nm_symbol_types.c for nm in /home/barthe_g/rendu/tek2/unix_memoire/PSU_2015_nmobjdump
** 
** Made by Barthelemy Gouby
** Login   <barthe_g@epitech.net>
** 
** Started on  Thu Feb 18 12:23:57 2016 Barthelemy Gouby
** Last update Thu Feb 18 13:44:44 2016 Barthelemy Gouby
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
  if (ELF64_ST_BIND(sym->st_info) == STB_WEAK && ELF64_ST_TYPE(sym->st_info) == STT_OBJECT)
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

char		test_common(Elf64_Sym *sym, Elf64_Shdr *shdr)
{
  (void) shdr;
  return (sym->st_shndx == SHN_COMMON ? 'C' : 0);
}

char		test_uninitialized(Elf64_Sym *sym, Elf64_Shdr *shdr)
{
  if (shdr[sym->st_shndx].sh_type == SHT_NOBITS
      && shdr[sym->st_shndx].sh_flags == (SHF_ALLOC | SHF_WRITE))
    return ('B');
  return (0);
}

char		test_readonly(Elf64_Sym *sym, Elf64_Shdr *shdr)
{
  if (shdr[sym->st_shndx].sh_type == SHT_PROGBITS
      && shdr[sym->st_shndx].sh_flags == SHF_ALLOC)
    return ('R');
  return (0);
}

char		test_initialized(Elf64_Sym *sym, Elf64_Shdr *shdr)
{
  if ((shdr[sym->st_shndx].sh_type == SHT_PROGBITS
       && shdr[sym->st_shndx].sh_flags == (SHF_ALLOC | SHF_WRITE))
      || shdr[sym->st_shndx].sh_type == SHT_DYNAMIC)
    return ('D');
  return (0);
}

char		test_text(Elf64_Sym *sym, Elf64_Shdr *shdr)
{
  if (shdr[sym->st_shndx].sh_type == SHT_PROGBITS
      && shdr[sym->st_shndx].sh_flags == (SHF_ALLOC | SHF_EXECINSTR))
    return ('T');
  return (0);
}

char		get_symbol_type(Elf64_Sym *sym, t_sym_info *sym_info)
{
  char		(*test_funcs[11])(Elf64_Sym *sym_struct, Elf64_Shdr *shdr) = {test_unique,
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
