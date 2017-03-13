/*
** server_states.c for MyIrc in /home/lks/rendu/PSU_2014_myirc/auzou_t/server
** 
** Made by Thibaud Auzou
** Login   <auzou_t@epitech.net>
** 
** Started on  Mon Apr  6 14:31:53 2015 Thibaud Auzou
** Last update Thu Apr  9 09:39:40 2015 Thibaud Auzou
*/

#include "server.h"

int			server_running(int shutdown)
{
  static int		running = 1;

  if (shutdown)
    running = 0;
  return (running);
}

void			shutdown_server(int signal)
{
  server_running(1);
  get_fd_env(DESTROY);
  chan_list(DESTROY);
  get_queue(DESTROY);
  if (signal == SIGINT || signal == SIGPIPE)
    {
      print_warning("\n[FORCED] Server is shutting down...\n");
      exit(EXIT_FAILURE);
    }
  else if (signal == SIGUSR1)
    print_warning("[NORMAL] Server is shutting down...\n");
}
