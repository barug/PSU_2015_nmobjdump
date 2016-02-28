/*
** objdump_architecture.c for objdump in /home/barthe_g/rendu/tek2/unix_memoire/PSU_2015_nmobjdump
** 
** Made by Barthelemy Gouby
** Login   <barthe_g@epitech.net>
** 
** Started on  Sun Feb 28 22:00:26 2016 Barthelemy Gouby
** Last update Sun Feb 28 22:00:37 2016 Barthelemy Gouby
*/

#include "objdump_ressources.h"

char		*get_architecture(int type)
{
  t_arch_type	types[20] = {{EM_NONE, "Unknown"}, {EM_M32, "WE 32100"},
			     {EM_SPARC, "SPARC"}, {EM_386, "i386"},
			     {EM_68K, "m68k"}, {EM_88K, "m88k"},
			     {EM_860, "i860"}, {EM_MIPS, "MIPS RS3000"},
			     {EM_PARISC, "hp/pa"}, {EM_SPARC32PLUS, "SPARC +"},
			     {EM_PPC, "PowerPC"}, {EM_PPC64, "PowerPC64"},
			     {EM_S390, "IBM S/390"}, {EM_ARM, "ARM"},
			     {EM_SH, "superH"}, {EM_SPARCV9, "SPARCV9"},
			     {EM_IA_64, "IA-64"}, {EM_X86_64, "AMD64"},
			     {EM_VAX, "VAX"}};
  int		i;

  i = 0;
  while (i <= 20)
    {
      if (type == types[i].type)
	return (types[i].type_name);
      i++;
    }
  return ("Unknown");
}
