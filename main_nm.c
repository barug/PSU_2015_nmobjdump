/*
** main_nm.c for nm in /home/barthe_g/rendu/tek2/unix_memoire/PSU_2015_nmobjdump
** 
** Made by Barthelemy Gouby
** Login   <barthe_g@epitech.net>
** 
** Started on  Tue Feb 16 11:00:20 2016 Barthelemy Gouby
** Last update Thu Feb 18 12:10:23 2016 Barthelemy Gouby
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
