/*
** server_buffer.c for MyIrc in /home/lks/rendu/PSU_2014_myirc/auzou_t
** 
** Made by Thibaud Auzou
** Login   <auzou_t@epitech.net>
** 
** Started on  Mon Apr  6 16:57:28 2015 Thibaud Auzou
** Last update Mon Apr  6 16:59:26 2015 Thibaud Auzou
*/

#include "server.h"

char		*buffer(void)
{
  static char	buff[BUFF_SIZE];
  static int	first = 1;

  if (first)
    {
      memset(buff, 0, BUFF_SIZE);
      first ^= first;
    }
  return (buff);
}
