/*
** server_sockets.c for MyIrc in /home/lks/rendu/PSU_2014_myirc/auzou_t/server
** 
** Made by Thibaud Auzou
** Login   <auzou_t@epitech.net>
** 
** Started on  Mon Apr  6 14:33:46 2015 Thibaud Auzou
** Last update Sat Apr 11 18:23:43 2015 Thibaud Auzou
*/

#include "server.h"

int			create_sock_server(int port)
{
  t_sockaddr		addr;
  t_fd			server;

  server._fd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
  if (server._fd == -1)
    return (print_error("ERROR [socket] :", 1));
  addr.sin_family = AF_INET;
  addr.sin_port = htons(port);
  addr.sin_addr.s_addr = INADDR_ANY;
  if (bind(server._fd, (const struct sockaddr *)(&addr), sizeof(addr)) == -1)
    return (print_error("ERROR [bind] :", 1));
  if (listen(server._fd, MAX_FD - 1) == -1)
    return (print_error("ERROR [listen] :", 1));
  server._state = SERVER;
  server._read = &create_sock_client;
  server._write = NULL;
  return (add_fd_to_env(&server));
}

int			create_sock_client(t_fd *server)
{
  t_sockaddr		addr;
  t_fd			client;
  socklen_t		addrlen;

  addrlen = sizeof(t_sockaddr);
  client._fd = accept(server->_fd, (struct sockaddr *)(&addr), &addrlen);
  if (client._fd == -1)
    return (print_error("ERROR [accept] :", 1));
  memset(client._buff, 0, BUFF_SIZE);
  client._pos = 0;
  client._clean = 0;
  client._state = CLIENT;
  client._read = &read_from_client;
  client._write = &write_to_client;
  memset(client._client._nick, 0 , NICK_SIZE);
  memset(client._client._chans, 0, sizeof(client._client._chans));
  client._client._connected = 0;
  client._client._welcomed = 0;
  return (add_fd_to_env(&client));
}
