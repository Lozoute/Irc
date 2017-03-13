/*
** print_warning.c for MyIrc in /home/auzou_t/rendu/PSU_2014_myirc/
** 
** Made by Thibaud Auzou
** Login   <auzou_t@epitech.net>
** 
** Started on  Sun Apr 12 18:33:36 2015 Thibaud Auzou
** Last update Sun Apr 12 18:34:12 2015 Thibaud Auzou
*/

#include "myirc.h"

int			print_warning(const char *warning)
{
  fprintf(stderr, "\x1b[1;33m%s\x1b[0m\n", warning);
  return (NOK);
}
