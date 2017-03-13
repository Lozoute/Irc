/*
** client_cmd_msg.c for MyIrc in /home/auzou_t/rendu/PSU_2014_myirc/
** 
** Made by Thibaud Auzou
** Login   <auzou_t@epitech.net>
** 
** Started on  Sun Apr 12 18:47:49 2015 Thibaud Auzou
** Last update Sun Apr 12 18:50:50 2015 Thibaud Auzou
*/

#include "client.h"

static char		*get_start_of_msg(t_fd_client *client)
{
  int			i;
  char			*b;

  b = client->_buff;
  for (i = 0; b[i] && b[i] == ' '; ++i);
  for (; b[i] && b[i] != ' '; ++i);
  for (; b[i] && b[i] == ' '; ++i);
  for (; b[i] && b[i] != ' '; ++i);
  for (; b[i] && b[i] == ' '; ++i);
  return (&(b[i]));
}

int		cmd_msg(t_fd_client *client)
{
  char		buff[BUFF_SIZE];
  char		*d;
  char		*msg;

  if ((d = strtok(NULL, " ")) == NULL)
    return (print_warning("/msg [dest] [msg] --> Dest Is Missing"));
  if ((msg = strtok(NULL, " ")) == NULL)
    return (print_warning("/msg [dest] [msg] --> Msg Is Missing"));
  msg = get_start_of_msg(client);
  sprintf(buff, "PRIVMSG %s :%s\r\n", d, msg);
  return (client->_write(buff));
}
