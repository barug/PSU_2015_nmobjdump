/*
** nm_process_file.c for nm in /home/barthe_g/rendu/tek2/unix_memoire/PSU_2015_nmobjdump
** 
** Made by Barthelemy Gouby
** Login   <barthe_g@epitech.net>
** 
** Started on  Thu Feb 18 12:08:32 2016 Barthelemy Gouby
** Last update Thu Feb 18 15:13:00 2016 Barthelemy Gouby
*/

#include "nm_ressources.h"

t_sym_info	get_symboles_info(void *data)
{
  Elf64_Ehdr	*header;
  Elf64_Shdr	*section_header_table;
  char		*section_names;
  t_sym_info	sym_info;
  int		i;

  i = 0;
  header = (Elf64_Ehdr*) data;
  section_header_table = data + header->e_shoff;
  sym_info.shdr = section_header_table;
  section_names = data + section_header_table[header->e_shstrndx].sh_offset;
  while (i < header->e_shnum)
    {
      if (strcmp(section_names + section_header_table[i].sh_name, ".strtab") == 0)
	sym_info.symbol_names = data + section_header_table[i].sh_offset;
      if (strcmp(section_names + section_header_table[i].sh_name, ".symtab") == 0)
	{
	  sym_info.symbol_table = data + section_header_table[i].sh_offset;
	  sym_info.st_entry_size = section_header_table[i].sh_entsize;
	  sym_info.st_size = section_header_table[i].sh_size;
	  sym_info.st_length = sym_info.st_size / sym_info.st_entry_size;
	}
      i++;
    }
  return (sym_info);
}

int		compare_symboles_names(const void *sym1, const void *sym2, void *sym_info)
{
  size_t	i;
  size_t	j;
  size_t	k;
  char		*name1;
  char		*name2;

  i = 0;
  name1 = ((t_sym_info*)(sym_info))->symbol_names +  ((Elf64_Sym*)(sym1))->st_name;
  name2 = ((t_sym_info*)(sym_info))->symbol_names +  ((Elf64_Sym*)(sym2))->st_name;
  while (i < strlen(name1) && !isalpha(name1[i]))
    i++;
  j = i;
  i = 0;
  while (i < strlen(name2) && !isalpha(name2[i]))
    i++;
  k = i;
  return (strcasecmp(&(name1[j]), &(name2[k])));
}

void		display_symbols(Elf64_Sym *sym_tab, t_sym_info *sym_info, int tab_length)
{
  int		i;

  i = 0;
  while (i < tab_length)
    {
      if (sym_tab[i].st_value)
	printf("%016x %c %s\n", (unsigned int) sym_tab[i].st_value,
	       get_symbol_type(&(sym_tab[i]), sym_info),
	       sym_info->symbol_names + sym_tab[i].st_name);
      else
	printf("%16c %c %s\n", ' ', get_symbol_type(&(sym_tab[i]), sym_info),
	       sym_info->symbol_names + sym_tab[i].st_name);
      i++;
    }
}

int		analyse_file_data(void	*data, t_arguments *arguments)
{
  t_sym_info	sym_info;
  Elf64_Sym	*sym_sort_tab;
  size_t	i;
  size_t	j;

  i = 0;
  j = 0;
  sym_info = get_symboles_info(data);
  if ((sym_sort_tab = malloc((sym_info.st_length * sizeof(*sym_sort_tab)))) == NULL)
    return (-1);
  while (i < sym_info.st_length)
    {
      if (sym_info.symbol_table[i].st_name)
	sym_sort_tab[j++] = sym_info.symbol_table[i];
      i++;
    }
  qsort_r(sym_sort_tab, j, sym_info.st_entry_size, compare_symboles_names, &sym_info);
  display_symbols(sym_sort_tab, &sym_info, j);
  (void) arguments;
  return (0);
}
