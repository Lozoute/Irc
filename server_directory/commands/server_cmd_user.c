/*
** server_cmd_user.c for MyIrc in /home/lks/rendu/PSU_2014_myirc/auzou_t/
** 
** Made by Thibaud Auzou
** Login   <auzou_t@epitech.net>
** 
** Started on  Wed Apr  8 15:44:02 2015 Thibaud Auzou
** Last update Sun Apr 12 18:52:35 2015 Thibaud Auzou
*/

#include "server.h"

int			cmd_user(t_fd *client)
{
  char			*nick;
  char			*host;
  char			*server;
  char			*realname;

  if (client->_client._connected)
    return (add_msg_to_queue(client, "462 %s\r\n", E_462));
  if ((nick = strtok(NULL, " ")) == NULL)
    return (add_msg_to_queue(client, "461 USER %s\r\n", E_461));
  if ((host = strtok(NULL, " ")) == NULL)
    return (add_msg_to_queue(client, "461 USER %s\r\n", E_461));
  if ((server = strtok(NULL, " ")) == NULL)
    return (add_msg_to_queue(client, "461 USER %s\r\n", E_461));
  if ((realname = strtok(NULL, " ")) == NULL)
    return (add_msg_to_queue(client, "461 USER %s\r\n", E_461));
  client->_client._connected = !client->_client._connected;
  if (strlen(client->_client._nick) > 0 && !client->_client._welcomed)
    return (send_welcome_msg(client));
  return (OK);
}
