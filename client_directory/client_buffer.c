/*
** client_buffer.c for MyIrc in /home/auzou_t/rendu/PSU_2014_myirc/
** 
** Made by Thibaud Auzou
** Login   <auzou_t@epitech.net>
** 
** Started on  Sun Apr 12 18:42:05 2015 Thibaud Auzou
** Last update Sun Apr 12 18:42:11 2015 Thibaud Auzou
*/

#include "client.h"

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
