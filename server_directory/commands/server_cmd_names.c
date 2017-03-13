/*
** server_cmd_names.c for MyIrc in /home/lks/rendu/PSU_2014_myirc/auzou_t/
** 
** Made by Thibaud Auzou
** Login   <auzou_t@epitech.net>
** 
** Started on  Wed Apr  8 15:46:11 2015 Thibaud Auzou
** Last update Sun Apr 12 18:52:54 2015 Thibaud Auzou
*/

#include "server.h"

static int		display_all_names(t_users_list *users, t_fd *client)
{
  char			*nick;

  for (; users != NULL; users = users->_next)
    {
      nick = users->_user->_client._nick;
      if (users->_next == NULL)
	{
	  if (add_msg_to_queue(client, "%s", nick) == ERROR)
	    return (ERROR);
	}
      else if (add_msg_to_queue(client, "%s ", nick) == ERROR)
	return (ERROR);
    }
  return (OK);
}

int			cmd_names(t_fd *client)
{
  char			*chan_name;
  t_chan_list		*chans;
  char			*nick;
  char			*name;

  chan_name = strtok(NULL, " ");
  nick = client->_client._nick;
  for (chans = get_chan_list(); chans != NULL; chans = chans->_next)
    {
      if (!chan_name || !strcmp(chan_name, chans->_chan._name))
	{
	  name = chans->_chan._name;
	  if (add_msg_to_queue(client, "353 %s %s :", nick, name) == ERROR)
	    return (ERROR);
	  if (display_all_names(chans->_chan._users, client) == ERROR)
	    return (ERROR);
	  if (add_msg_to_queue(client, "\r\n") == ERROR)
	    return (ERROR);
	}
    }
  (chan_name) ? (name = chan_name) : (name = "*");
  if (add_msg_to_queue(client, "366 %s %s %s\r\n", nick, name, R_366) == ERROR)
    return (ERROR);
  return (OK);
}
