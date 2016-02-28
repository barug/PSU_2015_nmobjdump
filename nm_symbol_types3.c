/*
** nm_symbol_types3.c for nmobjdump in /home/barthe_g/rendu/tek2/unix_memoire/PSU_2015_nmobjdump
** 
** Made by Barthelemy Gouby
** Login   <barthe_g@epitech.net>
** 
** Started on  Fri Feb 26 17:50:15 2016 Barthelemy Gouby
** Last update Fri Feb 26 17:54:45 2016 Barthelemy Gouby
*/

#include "nm_ressources.h"

char		test_common(Elf64_Sym *sym, Elf64_Shdr *shdr)
{
  (void) shdr;
  return (sym->st_shndx == SHN_COMMON ? 'C' : 0);
}

char		test_uninitialized(Elf64_Sym *sym, Elf64_Shdr *shdr)
{
  if (shdr[sym->st_shndx].sh_type == SHT_NOBITS
      && shdr[sym->st_shndx].sh_flags == (SHF_ALLOC | SHF_WRITE))
    {
      if (ELF64_ST_BIND(sym->st_info) == STB_LOCAL)
	return ('b');
      return ('B');
    }
  return (0);
}

char		test_readonly(Elf64_Sym *sym, Elf64_Shdr *shdr)
{
  if (shdr[sym->st_shndx].sh_type == SHT_PROGBITS
      && shdr[sym->st_shndx].sh_flags == SHF_ALLOC)
    {
      if (ELF64_ST_BIND(sym->st_info) == STB_LOCAL)
	return ('r');
      return ('R');
    }
  return (0);
}

char		test_initialized(Elf64_Sym *sym, Elf64_Shdr *shdr)
{
  if ((shdr[sym->st_shndx].sh_type == SHT_PROGBITS
       && shdr[sym->st_shndx].sh_flags == (SHF_ALLOC | SHF_WRITE))
      || shdr[sym->st_shndx].sh_type == SHT_DYNAMIC)
    {
      if (ELF64_ST_BIND(sym->st_info) == STB_LOCAL)
	return ('d');
      return ('D');
    }
  return (0);
}

char		test_text(Elf64_Sym *sym, Elf64_Shdr *shdr)
{
  if (shdr[sym->st_shndx].sh_type == SHT_PROGBITS
      && shdr[sym->st_shndx].sh_flags == (SHF_ALLOC | SHF_EXECINSTR))
    {
      if (ELF64_ST_BIND(sym->st_info) == STB_LOCAL)
	return ('t');
      return ('T');
    }
  return (0);
}
