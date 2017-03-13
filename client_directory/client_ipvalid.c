/*
** client_ipvalid.c for MyIrc in /home/auzou_t/rendu/PSU_2014_myirc/
** 
** Made by Thibaud Auzou
** Login   <auzou_t@epitech.net>
** 
** Started on  Sun Apr 12 18:41:11 2015 Thibaud Auzou
** Last update Sun Apr 12 18:41:17 2015 Thibaud Auzou
*/

#include "client.h"

int				isip_valid(char *ip)
{
  int				i;
  int				j;

  if (ip == NULL || strlen(ip) > 15)
    return (ERROR);
  j = 0;
  i = 0;
  while (ip[i] != '\0')
    {
      if (isdigit(ip[i]))
	{
	  if (j < 3)
	    ++j;
	  else
	    return (ERROR);
	}
      else if (ip[i] == '.')
	j = 0;
      else
	return (ERROR);
      ++i;
    }
  return (OK);
}
