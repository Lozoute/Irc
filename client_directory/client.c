/*
** client.c for MyIrc in /home/auzou_t/rendu/PSU_2014_myirc/client_directory
** 
** Made by Thibaud Auzou
** Login   <auzou_t@epitech.net>
** 
** Started on  Sun Apr 12 18:42:21 2015 Thibaud Auzou
** Last update Sun Apr 12 21:13:01 2015 Thibaud Auzou
*/

#include "client.h"

int				main(void)
{
  int				error;

  error = launch_client();
  if (error == ERROR)
    shutdown_client(SIGINT);
  shutdown_client(SIGUSR1);
  return (OK);
}

int				print_prompt(t_fd_client *client)
{
  char				*chan;
  static int			go = 1;

  if (client && go)
    {
      go = 0;
      (client->_curr_chan) ? (chan = client->_curr_chan->_name) : (chan = "");
      printf("\x1b[1;34m%s\x1b[0m@\x1b[1;32m%s\x1b[0m$>", client->_nick, chan);
      fflush(stdout);
    }
  else if (!client)
    go = 1;
  return (OK);
}

int				launch_client(void)
{
  t_fd_client			*client;
  t_protoent			*pe;

  client = get_client_env(GET);
  if (!(pe = getprotobyname(PROTO_NAME)))
    return (print_error("ERROR [getprotobyname]", 0));
  if ((client->_fd = socket(AF_INET, SOCK_STREAM, pe->p_proto)) == -1)
    return (print_error("ERROR [socket] :", 1));
  if (signal(SIGINT, shutdown_client) == SIG_ERR)
    return (print_error("ERROR [signal] :", 1));
  if (signal(SIGPIPE, shutdown_client) == SIG_ERR)
    return (print_error("ERROR [signal] :", 1));
  if (print_prompt(client) == ERROR)
    return (ERROR);
  while (client_running(0))
    {
      if (client_run() == ERROR)
	return (ERROR);
    }
  return (OK);
}

static int			set_fd(fd_set *read,
				       t_fd_client *client)
{
  int				b;

  b = 1;
  if (client->_connected)
    {
      FD_SET(client->_fd, read);
      (b <= client->_fd) ? (b = client->_fd + 1) : (b |= b);
    }
  return (b);
}

int				client_run(void)
{
  fd_set			read_set;
  t_fd_client			*client;
  int				bigger;
  int				nbits;
  t_timeval			tv;

  tv.tv_sec = 0;
  tv.tv_usec = 50000;
  FD_ZERO(&read_set);
  FD_SET(STDIN, &read_set);
  client = get_client_env(GET);
  bigger = set_fd(&read_set,  client);
  if ((nbits = select(bigger, &read_set, NULL, NULL, &tv)) == -1)
    return (print_error("ERROR [select] :", 1));
  else if (nbits == 0)
    return (print_prompt(client));
  print_prompt(NULL);
  if (FD_ISSET(client->_fd, &read_set))
    if (client->_read(client->_fd) == ERROR)
      return (ERROR);
  if (FD_ISSET(STDIN, &read_set))
    if (client->_read(STDIN) == ERROR)
      return (ERROR);
  return (OK);
}
