/*
** client_cmd_connect.c for MyIrc in /home/auzou_t/rendu/PSU_2014_myirc/
** 
** Made by Thibaud Auzou
** Login   <auzou_t@epitech.net>
** 
** Started on  Sun Apr 12 18:46:46 2015 Thibaud Auzou
** Last update Sun Apr 12 20:52:00 2015 Thibaud Auzou
*/

#include "client.h"

int		cmd_connect(t_fd_client *client)
{
  char		*ip;
  char		*c_port;
  char		buff[BUFF_SIZE];

  if (client->_connected)
    return (print_warning("Already Connected"));
  if (strlen(client->_nick) < 1)
    return (print_warning("Please Nick Before Connect"));
  if ((ip = strtok(NULL, ":")) == NULL)
    return (print_warning("/connect : [ip:port] --> Ip Is Missing"));
  if ((c_port = strtok(NULL, ":")) == NULL)
    c_port = "6667";
  if (connect_client(ip, atoi(c_port)) == ERROR)
    return (NOK);
  sprintf(buff, "NICK %s\r\n", client->_nick);
  client_write_to_serv(buff);
  sprintf(buff, "USER %s %s %s :Unknown\r\n", client->_nick, ip, c_port);
  return (client_write_to_serv(buff));
}

int				connect_client(char *ip, int port)
{
  t_sockaddr			addr;
  t_fd_client			*client;

  client = get_client_env(GET);
  client->_connected = 0;
  addr.sin_family = AF_INET;
  addr.sin_port = htons(port);
  addr.sin_addr.s_addr = inet_addr(ip);
  if (connect(client->_fd, (struct sockaddr *)&addr, sizeof(addr)) == -1)
    return (print_error("ERROR [connect]", 1));
  client->_connected = 1;
  return (OK);
}
