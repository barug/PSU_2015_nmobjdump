/*
** main_nm.c for nm in /home/barthe_g/rendu/tek2/unix_memoire/PSU_2015_nmobjdump
** 
** Made by Barthelemy Gouby
** Login   <barthe_g@epitech.net>
** 
** Started on  Tue Feb 16 11:00:20 2016 Barthelemy Gouby
** Last update Thu Feb 18 12:03:46 2016 Barthelemy Gouby
*/

#include "nm_ressources.h"

int		get_arguments(int argc, char **argv, t_arguments *arguments)
{
  int	i;
  int	files_nbr;

  i = 1;
  files_nbr = 0;
  arguments->file_paths = NULL;
  while (i < argc)
    {
      if (argv[i][0] != '-')
	{
	  if ((arguments->file_paths = realloc(arguments->file_paths, (files_nbr + 2) * sizeof(char*))) == NULL)
	    return (-1);
	  arguments->file_paths[files_nbr] = argv[i];
	  files_nbr++;
	}
      i++;
    }
  arguments->file_paths[files_nbr] = NULL;
  return (0);
}

void		*open_file(char *file_path)
{
  int		fd;
  void		*data;
  struct stat	file_infos;

  if ((fd = open(file_path, O_RDONLY)) == -1)
    return (NULL);
  if (fstat(fd, &file_infos) == -1)
    return (NULL);
  if ((data = mmap(NULL, file_infos.st_size, PROT_READ, MAP_PRIVATE, fd, 0)) == (void*) -1)
    return (NULL);
  return (data);
}

int check_header_type(Elf64_Ehdr * data)
{
  if (data->e_ident[EI_MAG0] != ELFMAG0 ||
      data->e_ident[EI_MAG1] != ELFMAG1 ||
      data->e_ident[EI_MAG2] != ELFMAG2 ||
      data->e_ident[EI_MAG3] != ELFMAG3 ||
      data->e_ident[EI_CLASS] != ELFCLASS64)
    return (-1);
  return (0);
}

t_sym_info	get_symboles_info(void	*data)
{
  Elf64_Ehdr	*header;
  Elf64_Shdr	*section_header_table;
  char		*section_names;
  t_sym_info	sym_info;
  int		i;

  i = 0;
  header = (Elf64_Ehdr*) data;
  section_header_table = data + header->e_shoff;
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

int		analyse_file_data(void	*data, t_arguments *arguments)
{
  t_sym_info	sym_info;
  Elf64_Sym	*sym_sort_tab;
  size_t	i;
  size_t	j;

  i = 0;
  j = 0;
  if (check_header_type((Elf64_Ehdr*) data) == -1)
    return (-1);
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
  i = 0;
  while (i < j)
    {
      if (sym_sort_tab[i].st_value)
	printf("%016x %s\n",(unsigned int) sym_sort_tab[i].st_value,
	       sym_info.symbol_names + sym_sort_tab[i].st_name);
      else
	printf("%16c %s\n",' ' , sym_info.symbol_names + sym_sort_tab[i].st_name);
      i++;
    }
  (void) arguments;
  return (0);
}

int		main(int argc, char **argv)
{
  t_arguments	arguments;
  int		i;
  void		*current_file_data;

  i = 0;
  if (get_arguments(argc, argv, &arguments) == -1)
    return (-1);
  while (arguments.file_paths[i])
    {
      if((current_file_data = open_file(arguments.file_paths[i++])) == NULL)
	return (-1);
      if (analyse_file_data(current_file_data, &arguments) == -1)
      	return (-1);
    }
  return (0);
}
