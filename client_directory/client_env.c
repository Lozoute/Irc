/*
** client_env.c for MyIrc in /home/auzou_t/rendu/PSU_2014_myirc/
** 
** Made by Thibaud Auzou
** Login   <auzou_t@epitech.net>
** 
** Started on  Sun Apr 12 18:42:48 2015 Thibaud Auzou
** Last update Sun Apr 12 20:51:38 2015 Thibaud Auzou
*/

#include "client.h"

t_fd_client		*get_client_env(int action)
{
  static t_fd_client	client_env;
  static int		first = 1;
  char			*username;

  if (action == DESTROY || first)
    {
      if (!first && client_env._fd != -1)
	close(client_env._fd);
      client_env._fd = -1;
      if ((username = getenv("USER")) == NULL)
	memset(client_env._nick, 0, NICK_SIZE);
      else
	strcpy(client_env._nick, username);
      client_env._read = &client_read;
      client_env._connected = 0;
      client_env._write = &client_write_to_serv;
      client_env._curr_chan = NULL;
      first ^= first;
    }
  return (&client_env);
}
