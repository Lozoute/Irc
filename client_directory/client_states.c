/*
** client_states.c for MyIrc in /home/auzou_t/rendu/PSU_2014_myirc/
** 
** Made by Thibaud Auzou
** Login   <auzou_t@epitech.net>
** 
** Started on  Sun Apr 12 18:40:49 2015 Thibaud Auzou
** Last update Sun Apr 12 18:40:55 2015 Thibaud Auzou
*/

#include "client.h"

int				client_running(int shutdown)
{
  static int			running = 1;

  if (shutdown)
    running = 0;
  return (running);
}

void				shutdown_client(int signal)
{
  client_running(1);
  get_client_env(DESTROY);
  chan_list(DESTROY);
  if (signal == SIGINT || signal == SIGPIPE)
    {
      print_warning("\n[FORCED] Client is shutting down...");
      exit(EXIT_FAILURE);
    }
  else if (signal == SIGUSR1)
    print_warning("Disconnected. See You !\n");
}
