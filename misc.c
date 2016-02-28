/*
** main_nm.c for nm in /home/barthe_g/rendu/tek2/unix_memoire/PSU_2015_nmobjdump
** 
** Made by Barthelemy Gouby
** Login   <barthe_g@epitech.net>
** 
** Started on  Tue Feb 16 11:00:20 2016 Barthelemy Gouby
** Last update Fri Feb 26 18:52:23 2016 Barthelemy Gouby
*/

#include "nm_ressources.h"

void		*open_file(char *file_path)
{
  int		fd;
  void		*data;
  struct stat	file_infos;

  if ((fd = open(file_path, O_RDONLY)) == -1)
    return (NULL);
  if (fstat(fd, &file_infos) == -1)
    return (NULL);
  if ((data = mmap(NULL, file_infos.st_size, PROT_READ,
		   MAP_PRIVATE, fd, 0)) == (void*) -1)
    return (NULL);
  return (data);
}

int		check_header_type(Elf64_Ehdr * data)
{
  if (data->e_ident[EI_MAG0] != ELFMAG0 ||
      data->e_ident[EI_MAG1] != ELFMAG1 ||
      data->e_ident[EI_MAG2] != ELFMAG2 ||
      data->e_ident[EI_MAG3] != ELFMAG3 ||
      data->e_ident[EI_CLASS] != ELFCLASS64)
    return (-1);
  return (0);
}

int		check_if_files(t_arguments *arguments, int *files_nbr)
{
  if (*files_nbr == 0)
    {
      if (!(arguments->file_paths = malloc(2 * sizeof(char*))))
	return (-1);
      if (!(arguments->file_paths[*files_nbr] = malloc(6 * sizeof(char))))
	return (-1);
      strcpy(arguments->file_paths[(*files_nbr)++], "a.out");
    }
  return (0);
}

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
	  if ((arguments->file_paths = realloc(arguments->file_paths,
					       (files_nbr + 2) * sizeof(char*))) == NULL)
	    return (-1);
	  arguments->file_paths[files_nbr] = argv[i];
	  files_nbr++;
	}
      i++;
    }
  if (check_if_files(arguments, &files_nbr) == -1)
    return (-1);
  arguments->file_paths[files_nbr] = NULL;
  arguments->number_of_files = files_nbr;
  return (0);
}
