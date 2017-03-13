/*
** server_env.c for MyIrc in /home/lks/rendu/PSU_2014_myirc/auzou_t/server
** 
** Made by Thibaud Auzou
** Login   <auzou_t@epitech.net>
** 
** Started on  Mon Apr  6 15:30:41 2015 Thibaud Auzou
** Last update Fri Apr 10 16:45:02 2015 Thibaud Auzou
*/

#include "server.h"

t_fd			*get_fd_env(int action)
{
  static t_fd		fd_env[MAX_FD];
  static int		first = 1;
  int			i;

  if (action == DESTROY || first)
    {
      for (i = 0; i < MAX_FD; ++i)
	{
	  if (!first && fd_env[i]._state != FREE)
	    close(fd_env[i]._fd);
	  fd_env[i]._fd = -1;
	  fd_env[i]._state = FREE;
	  fd_env[i]._read = NULL;
	  fd_env[i]._write = NULL;
	}
      first ^= first;
    }
  return (fd_env);
}

int			add_fd_to_env(t_fd *elem)
{
  int			i;
  t_fd			*env;

  env = get_fd_env(GET);
  for (i = 0; i < MAX_FD; ++i)
    {
      if (env[i]._state == FREE)
	{
	  memcpy(&(env[i]), elem, sizeof(t_fd));
	  return (OK);
	}
    }
  close(elem->_fd);
  return (print_warning("Unable To Add New Fd. Maximum Reached."));
}

int			rm_fd_from_env(int fd)
{
  int			i;
  t_fd			*env;

  env = get_fd_env(GET);
  for (i = 0; i < MAX_FD; ++i)
    {
      if (env[i]._fd == fd)
	{
	  close(env[i]._fd);
	  env[i]._fd = -1;
	  env[i]._state = FREE;
	  env[i]._read = NULL;
	  env[i]._write = NULL;
	  return (OK);
	}
    }
  return (print_warning("Unable To Remove Fd. Does Not Exists."));
}

t_fd			*get_client_from_env(int fd)
{
  t_fd			*env;
  int			i;

  env = get_fd_env(GET);
  for (i = 0; i < MAX_FD; ++i)
    if (env[i]._fd == fd)
      return (&(env[i]));
  return (NULL);
}

t_fd			*get_client_from_env_by_nick(char *nick)
{
  t_fd			*env;
  int			i;

  env = get_fd_env(GET);
  for (i = 0; i < MAX_FD; ++i)
    if (env[i]._state == CLIENT && !strcmp(env[i]._client._nick, nick))
      return (&(env[i]));
  return (NULL);
}
