/*
** server_read_functions.c for MyIrc in /home/lks/rendu/PSU_2014_myirc/auzou_t
** 
** Made by Thibaud Auzou
** Login   <auzou_t@epitech.net>
** 
** Started on  Mon Apr  6 16:45:54 2015 Thibaud Auzou
** Last update Sun Apr 12 14:12:54 2015 Thibaud Auzou
*/

#include "server.h"

static int	need_to_execute(t_fd *client, int exec)
{
  if (!exec)
    {
      client->_clean = 0;
      return (OK);
    }
  client->_clean = 1;
  client->_pos = 0;
  return (execute_command(client));
}

static int	cpy_to_client_buff(t_fd *client, char *msg, char *substr)
{
  memcpy(&(client->_buff[client->_pos]), msg, substr - msg);
  client->_pos = (client->_pos + (substr - msg)) % (BUFF_SIZE / 2);
  client->_buff[client->_pos] = 0;
  for (; (substr[0] == '\n' || substr[0] == '\r') && substr[0]; ++substr);
  strcpy(msg, substr);
  return (OK);
}

int		read_from_client(t_fd *client)
{
  char		msg[BUFF_SIZE];
  char		*substr;
  int		nb;

  if (client->_clean)
    memset(client->_buff, 0, BUFF_SIZE);
  if ((nb = read(client->_fd, msg, BUFF_SIZE / 2)) == -1)
    return (print_error("ERROR [read] :", 1));
  else if (nb == 0)
    return (cmd_quit(client));
  msg[nb] = 0;
  while ((substr = strstr(msg, "\r\n")) || (substr = strstr(msg, "\n")))
    {
      cpy_to_client_buff(client, msg, substr);
      if (need_to_execute(client, 1) == ERROR)
	return (ERROR);
      memset(client->_buff, 0, BUFF_SIZE);
    }
  if (strlen(msg))
    strcpy(&(client->_buff[client->_pos]), msg);
  client->_pos = (client->_pos + strlen(msg)) % (BUFF_SIZE / 2);
  client->_clean = 0;
  return (OK);
}
