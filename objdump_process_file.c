/*
** objdump_process_file.c for objdump in /home/barthe_g/rendu/tek2/unix_memoire/PSU_2015_nmobjdump
** 
** Made by Barthelemy Gouby
** Login   <barthe_g@epitech.net>
** 
** Started on  Thu Feb 18 14:33:13 2016 Barthelemy Gouby
** Last update Sun Feb 28 22:00:47 2016 Barthelemy Gouby
*/

#include "objdump_ressources.h"

void		display_header_info(Elf64_Ehdr *header)
{
  printf("file format elf64-x86-64\n");
  printf("architecture: %s, ", get_architecture(header->e_machine));
  printf("flags: 0x%08x\n",  header->e_type);
  printf("start adress Ox%x016x\n\n", (unsigned int) header->e_entry);
}

void		print_ascii(char *line_data, int offset, int section_size)
{
  int		i;

  i = 0;
  while (i < 16 && i + offset < section_size)
    {
      if (isprint(line_data[i]))
	printf("%c", line_data[i]);
      else
	printf(".");
      i++;
    }
  printf("\n");
}

void		display_section(Elf64_Shdr *section, char *section_names, void *data)
{
  unsigned char	*section_data;
  size_t	i;
  size_t	j;

  i = 0;
  j = 0;
  section_data = data + section->sh_offset;
  printf("contents of section %s:\n", section_names + section->sh_name);
  while (i < section->sh_size)
    {
      j = 0;
      printf("%04x ", (unsigned int) (section->sh_addr + i));
      while (j < 16)
	{
	  if (i + j < section->sh_size)
	    printf("%02x", section_data[i + j]);
	  else
	    printf("  ");
	  if ((j + 1) % 4 == 0 && j != 0)
	    printf(" ");
	  j++;
	}
      print_ascii((char*) section_data + i, i, section->sh_size);
      i += j;
    }
}

void		display_all_sections(void *data)
{
  Elf64_Ehdr	*header;
  Elf64_Shdr	*section_header_table;
  char		*section_names;
  int		i;

  i = 0;
  header = (Elf64_Ehdr*) data;
  section_header_table = data + header->e_shoff;
  section_names = data + section_header_table[header->e_shstrndx].sh_offset;
  while (i < header->e_shnum)
    {
      if (i != SHN_UNDEF && section_header_table[i].sh_type != SHT_STRTAB)
	display_section(&(section_header_table[i]), section_names, data);
      i++;
    }
}

int		analyse_file_data(void	*data, t_arguments *arguments)
{
  display_header_info((Elf64_Ehdr*) data);
  display_all_sections(data);
  (void) arguments;
  return (0);
}
