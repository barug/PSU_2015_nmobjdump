/*
** main_nm.c for nm in /home/barthe_g/rendu/tek2/unix_memoire/PSU_2015_nmobjdump
** 
** Made by Barthelemy Gouby
** Login   <barthe_g@epitech.net>
** 
** Started on  Thu Feb 18 16:15:09 2016 Barthelemy Gouby
** Last update Fri Feb 26 12:04:03 2016 Barthelemy Gouby
*/

#include "nm_ressources.h"

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
      printf("\n%s:\n", arguments.file_paths[i]);
      if((current_file_data = open_file(arguments.file_paths[i++])) == NULL)
	return (-1);
      if (check_header_type((Elf64_Ehdr*) current_file_data) == -1)
	return (-1);
      if (analyse_file_data(current_file_data, &arguments) == -1)
      	return (-1);
    }
  return (0);
}
