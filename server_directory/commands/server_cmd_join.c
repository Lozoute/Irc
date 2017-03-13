/*
** server_cmd_join.c for MyIrc in /home/lks/rendu/PSU_2014_myirc/auzou_t/
** 
** Made by Thibaud Auzou
** Login   <auzou_t@epitech.net>
** 
** Started on  Wed Apr  8 15:45:15 2015 Thibaud Auzou
** Last update Sun Apr 12 18:52:59 2015 Thibaud Auzou
*/

#include "server.h"

int			cmd_join(t_fd *client)
{
  char			*chan_name;
  t_chan		*chan;
  char			buff[BUFF_SIZE];

  strcpy(buff, "#");
  if ((chan_name = strtok(NULL, " ")) == NULL)
    return (add_msg_to_queue(client, "461 JOIN %s\r\n", E_461));
  strcat(buff, (chan_name[0] == '#') ? (&(chan_name[1])) : (chan_name));
  if (add_new_chan(buff) == ERROR)
    return (ERROR);
  if ((chan = get_chan(buff)) == NULL)
    return (ERROR);
  if (chan->_size >= MAX_USER_CHAN)
    return (add_msg_to_queue(client, "471 %s %s\r\n", chan_name, E_471));
  if (already_in_chan(chan, client))
    return (NOK);
  if (add_chan_to_user(chan, client) == ERROR)
    return (add_msg_to_queue(client, "405 %s %s\r\n", chan_name, E_405));
  if (add_user_to_chan(client, chan) == ERROR)
    return (ERROR);
  sprintf(client->_buff, "NAMES %s", chan->_name);
  if (execute_command(client) == ERROR)
    return (ERROR);
  sprintf(buff, ":%s JOIN :%s\r\n", client->_client._nick, chan->_name);
  return (send_msg_to_chan(chan, client, buff));
}

int			add_chan_to_user(t_chan *chan, t_fd *client)
{
  int			i;
  char			*n;
  char			*c;
  char			*t;

  for (i = 0; i < MAX_CHAN; ++i)
    {
      if (!client->_client._chans[i])
	{
	  n = client->_client._nick;
	  c = chan->_name;
	  t = chan->_topic;
	  client->_client._chans[i] = chan;
	  if (add_msg_to_queue(client, "332 %s %s :%s\r\n", n, c, t) == ERROR)
	    return (ERROR);
	  return (OK);
	}
    }
  return (ERROR);
}

int			already_in_chan(t_chan *chan, t_fd *client)
{
  int			i;

  for (i = 0; i < MAX_CHAN; ++i)
    {
      if (client->_client._chans[i] == chan)
	return (1);
    }
  return (0);
}
