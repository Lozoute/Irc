/*
** server_cmd_privmsg.c for MyIrc in /home/lks/rendu/PSU_2014_myirc/auzou_t/
** 
** Made by Thibaud Auzou
** Login   <auzou_t@epitech.net>
** 
** Started on  Wed Apr  8 15:46:37 2015 Thibaud Auzou
** Last update Sun Apr 12 18:52:45 2015 Thibaud Auzou
*/

#include "server.h"

static char		*get_start_of_msg(t_fd *client)
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

int			cmd_privmsg(t_fd *client)
{
  char			*nick;
  char			*d;
  char			*msg;
  void			*s_d;
  char			buff[BUFF_SIZE];

  nick = client->_client._nick;
  if ((d = strtok(NULL, " ")) == NULL)
    return (add_msg_to_queue(client, "411 %s %s (PRIVMSG)\r\n", nick, E_411));
  if ((msg = strtok(NULL, " ")) == NULL)
    return (add_msg_to_queue(client, "412 %s %s\r\n", nick, E_412));
  msg = get_start_of_msg(client);
  sprintf(buff, ":%s PRIVMSG %s :%s\r\n", nick, d, msg);
  if (d[0] == '#')
    {
      if ((s_d = get_chan(d)) == NULL)
	return (add_msg_to_queue(client, "401 %s %s %s\r\n", nick, d, E_401));
      return (send_msg_to_chan((t_chan *)(s_d), client, buff));
    }
  if ((s_d = get_client_from_env_by_nick(d)) == NULL)
    return (add_msg_to_queue(client, "401 %s %s %s\r\n", nick, d, E_401));
  return (add_msg_to_queue((t_fd *)(s_d), "%s", buff));
}
