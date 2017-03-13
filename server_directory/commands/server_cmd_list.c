/*
** server_cmd_list.c for MyIrc in /home/lks/rendu/PSU_2014_myirc/auzou_t/
** 
** Made by Thibaud Auzou
** Login   <auzou_t@epitech.net>
** 
** Started on  Wed Apr  8 15:44:51 2015 Thibaud Auzou
** Last update Sun Apr 12 18:53:15 2015 Thibaud Auzou
*/

#include "server.h"

static int		send_chan(char *t, char *na, t_fd *client, char *n)
{
  if (add_msg_to_queue(client, "322 %s %s 7 :%s\r\n", n, na, t) == ERROR)
    return (ERROR);
  return (OK);
}

int			cmd_list(t_fd *client)
{
  char			*search;
  char			*n;
  char			*na;
  char			*t;
  t_chan_list		*tmp;

  search = strtok(NULL, " ");
  n = client->_client._nick;
  if (add_msg_to_queue(client, "321 %s %s\r\n", n, R_321) == ERROR)
    return (ERROR);
  for (tmp = get_chan_list(); tmp != NULL; tmp = tmp->_next)
    {
      if (!search || strstr(tmp->_chan._name, search))
	{
	  na = tmp->_chan._name;
	  t = tmp->_chan._topic;
	  if (send_chan(t, na, client, n) == ERROR)
	    return (ERROR);
	}
    }
  if (add_msg_to_queue(client, "323 %s %s\r\n", n, R_323) == ERROR)
    return (ERROR);
  return (OK);
}
