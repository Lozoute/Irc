/*
** server_cmd_quit.c for MyIrc in /home/lks/rendu/PSU_2014_myirc/auzou_t/
** 
** Made by Thibaud Auzou
** Login   <auzou_t@epitech.net>
** 
** Started on  Wed Apr  8 15:47:57 2015 Thibaud Auzou
** Last update Sun Apr 12 18:53:27 2015 Thibaud Auzou
*/

#include "server.h"

int			cmd_quit(t_fd *client)
{
  int			i;
  char			b[BUFF_SIZE];
  char			*c;

  if (!client)
    return (ERROR);
  for (i = 0; i < MAX_CHAN; ++i)
    {
      if (client->_client._chans[i])
	{
	  c = client->_client._chans[i]->_name;
	  sprintf(b, ":%s QUIT %s\r\n", client->_client._nick, c);
	  if (send_msg_to_chan(client->_client._chans[i], client, b) == ERROR)
	    return (ERROR);
	  remove_user_from_chan(client, client->_client._chans[i]);
	}
    }
  remove_all_msg_to_user(client);
  rm_fd_from_env(client->_fd);
  return (OK);
}
