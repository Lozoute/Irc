/*
** server_cmd_nick.c for MyIrc in /home/lks/rendu/PSU_2014_myirc/auzou_t/
** 
** Made by Thibaud Auzou
** Login   <auzou_t@epitech.net>
** 
** Started on  Wed Apr  8 15:41:49 2015 Thibaud Auzou
** Last update Sun Apr 12 18:53:19 2015 Thibaud Auzou
*/

#include "server.h"

static int		send_nick_changed(t_fd *client, char *old)
{
  int			i;
  int			e;
  char			buff[BUFF_SIZE];

  for (i = 0; i < MAX_CHAN; ++i)
    {
      if (client->_client._chans[i])
	{
	  sprintf(buff, ":%s NICK :%s\r\n", old, client->_client._nick);
	  e = send_msg_to_chan(client->_client._chans[i], client, buff);
	  if (e == ERROR)
	    return (ERROR);
	}
    }
  return (OK);
}

int			cmd_nick(t_fd *client)
{
  char			*nick;
  char			old[BUFF_SIZE];

  if ((nick = strtok(NULL, " ")) == NULL)
    return (add_msg_to_queue(client, "431 %s\r\n", E_431));
  if (!strcmp(nick, client->_client._nick))
    return (OK);
  if (get_client_from_env_by_nick(nick))
    return (add_msg_to_queue(client, "433 %s %s\r\n", nick, E_433));
  if (strlen(nick) > NICK_SIZE - 1)
    return (add_msg_to_queue(client, "432 %s %s\r\n", nick, E_432));
  strcpy(old, client->_client._nick);
  strcpy(client->_client._nick, nick);
  if (client->_client._connected && !client->_client._welcomed)
    return (send_welcome_msg(client));
  return (send_nick_changed(client, old));
}

int			send_welcome_msg(t_fd *client)
{
  char			*n;

  n = client->_client._nick;
  if (add_msg_to_queue(client, "001 %s %s\r\n", n, R_001) == ERROR)
    return (ERROR);
  if (add_msg_to_queue(client, "002 %s %s\r\n", n, R_002) == ERROR)
    return (ERROR);
  if (add_msg_to_queue(client, "003 %s %s\r\n", n, R_003) == ERROR)
    return (ERROR);
  if (add_msg_to_queue(client, "004 %s %s\r\n", n, R_004) == ERROR)
    return (ERROR);
  if (add_msg_to_queue(client, "005 %s %s\r\n", n, R_005) == ERROR)
    return (ERROR);
  if (add_msg_to_queue(client, "375 %s %s\r\n", n, R_375) == ERROR)
    return (ERROR);
  if (add_msg_to_queue(client, "372 %s %s\r\n", n, R_372) == ERROR)
    return (ERROR);
  if (add_msg_to_queue(client, "376 %s %s\r\n", n, R_376) == ERROR)
    return (ERROR);
  client->_client._welcomed = !client->_client._welcomed;
  return (OK);
}
