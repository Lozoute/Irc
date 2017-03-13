/*
** client_read_functions.c for MyIrc in /home/auzou_t/rendu/PSU_2014_myirc/
** 
** Made by Thibaud Auzou
** Login   <auzou_t@epitech.net>
** 
** Started on  Sun Apr 12 18:43:05 2015 Thibaud Auzou
** Last update Sun Apr 12 21:18:09 2015 Thibaud Auzou
*/

#include "client.h"

int		client_read(int fd)
{
  if (fd == 0)
    return (read_from_user());
  return (read_from_server(fd));
}

int		read_from_user(void)
{
  char		*msg;
  int		nb;

  msg = buffer();
  memset(msg, 0, BUFF_SIZE);
  if ((nb = read(0, msg, BUFF_SIZE - 1)) == -1)
    return (print_error("ERROR [read] :", 1));
  msg[nb] = 0;
  if (nb == 0)
    {
      client_running(1);
      return (OK);
    }
  if (msg[nb - 1] == '\n')
    msg[nb - 1] = 0;
  return (execute_command_input(msg));
}

int		read_from_server(int fd)
{
  char		msg[BUFF_SIZE];
  int		nb;

  if ((nb = read(fd, msg, BUFF_SIZE / 2)) == -1)
    return (print_error("ERROR [read] :", 1));
  msg[nb] = 0;
  if (nb == 0)
    return (ERROR);
  printf("\n%s", msg);
  fflush(stdout);
  return (OK);
}
