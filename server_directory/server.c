/*
** server.c for MyIrc in /home/auzou_t/rendu/PSU_2014_myirc/server_directory
** 
** Made by Thibaud Auzou
** Login   <auzou_t@epitech.net>
** 
** Started on  Sun Apr 12 18:51:51 2015 Thibaud Auzou
** Last update Sun Apr 12 18:51:53 2015 Thibaud Auzou
*/

#include "server.h"

int				main(int argc, char **argv)
{
  int				i;
  int				error;

  if (argc < 2 || argv == NULL)
    return (print_error("Usage : ./server [port]", 0));
  for (i = 0; argv[1] && argv[1][i]; ++i)
    if (!isdigit(argv[1][i]))
      return (print_error("Not A Valid Port.", 0));
  error = create_sock_server(atoi(argv[1]));
  if (error != ERROR)
    error = launch_server();
  if (error == ERROR)
    shutdown_server(SIGINT);
  shutdown_server(SIGUSR1);
  return (OK);
}

int				launch_server(void)
{
  t_timeval			tv;
  fd_set			read_set;
  fd_set			write_set;

  if (signal(SIGINT, shutdown_server) == SIG_ERR)
    return (print_error("ERROR [signal] :", 1));
  if (signal(SIGPIPE, shutdown_server) == SIG_ERR)
    return (print_error("ERROR [signal] :", 1));
  tv.tv_usec = 0;
  while (server_running(0))
    if (monitor_env(&tv, &read_set, &write_set) == ERROR)
      return (ERROR);
  return (OK);
}

int				monitor_env(t_timeval *tv,
					    fd_set *read_set,
					    fd_set *write_set)
{
  t_fd				*env;
  int				i;
  int				bigger;
  int				nbits;

  FD_ZERO(read_set);
  FD_ZERO(write_set);
  env = get_fd_env(GET);
  bigger = set_fd(env, read_set, write_set);
  tv->tv_sec = 1;
  if ((nbits = select(bigger, read_set, write_set, NULL, tv)) == -1)
    return (print_error("ERROR [select] :", 1));
  fflush(stdout);
  if (nbits == 0)
    return (start_idle());
  stop_idle();
  for (i = 0; i < MAX_FD; ++i)
    {
      if (env[i]._state != FREE && FD_ISSET(env[i]._fd, read_set))
	if (env[i]._read(&(env[i])) == ERROR)
	  return (ERROR);
    }
  return (try_to_send_all_msg(write_set));
}

int				set_fd(t_fd *env,
				       fd_set *read_set,
				       fd_set *write_set)
{
  int				i;
  int				bigger;

  bigger ^= bigger;
  for (i = 0; i < MAX_FD; ++i)
    {
      if (env[i]._state != FREE)
	{
	  if (env[i]._read != NULL)
	    FD_SET(env[i]._fd, read_set);
	  if (env[i]._write != NULL && msg_queued(&(env[i])))
	    FD_SET(env[i]._fd, write_set);
	  bigger = env[i]._fd + 1;
	}
    }
  return (bigger);
}

int				msg_queued(t_fd *client)
{
  t_queue			*queue;

  for (queue = *(get_queue(GET)); queue != NULL; queue = queue->_next)
    {
      if (queue->_msg._dest == client)
	return (1);
    }
  return (0);
}
