/*
** server_cmd_part.c for MyIrc in /home/lks/rendu/PSU_2014_myirc/auzou_t/
** 
** Made by Thibaud Auzou
** Login   <auzou_t@epitech.net>
** 
** Started on  Wed Apr  8 15:45:47 2015 Thibaud Auzou
** Last update Sun Apr 12 18:52:49 2015 Thibaud Auzou
*/

#include "server.h"

int			cmd_part(t_fd *client)
{
  char			*chan_name;
  t_chan		*chan;
  char			buff[BUFF_SIZE];

  if ((chan_name = strtok(NULL, " ")) == NULL)
    return (add_msg_to_queue(client, "461 PART %s\r\n", E_461));
  if ((chan = get_chan(chan_name)) == NULL)
    return (add_msg_to_queue(client, "403 %s %s\r\n", chan_name, E_403));
  if (!already_in_chan(chan, client))
    return (add_msg_to_queue(client, "442 %s %s\r\n", chan_name, E_442));
  remove_chan_from_user(chan, client);
  remove_user_from_chan(client, chan);
  sprintf(buff, ":%s PART %s\r\n", client->_client._nick, chan->_name);
  return (send_msg_to_chan(chan, client, buff));
}

int			remove_chan_from_user(t_chan *chan, t_fd *client)
{
  int			i;

  for (i = 0; i < MAX_CHAN; ++i)
    {
      if (client->_client._chans[i] == chan)
	{
	  client->_client._chans[i] = NULL;
	  return (OK);
	}
    }
  return (ERROR);
}
