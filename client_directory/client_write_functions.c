/*
** client_write_functions.c for MyIrc in /home/auzou_t/rendu/PSU_2014_myirc/
** 
** Made by Thibaud Auzou
** Login   <auzou_t@epitech.net>
** 
** Started on  Sun Apr 12 18:40:21 2015 Thibaud Auzou
** Last update Sun Apr 12 18:40:32 2015 Thibaud Auzou
*/

#include "client.h"

int		client_write_to_serv(char *msg)
{
  t_fd_client	*client;

  client = get_client_env(GET);
  if (client->_fd != -1)
    return (write(client->_fd, msg, strlen(msg)));
  return (print_warning("You are not connected to any server"));
}
