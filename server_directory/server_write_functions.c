/*
** server_write_functions.c for MyIrc in /home/lks/rendu/PSU_2014_myirc/auzou_t
** 
** Made by Thibaud Auzou
** Login   <auzou_t@epitech.net>
** 
** Started on  Mon Apr  6 16:51:41 2015 Thibaud Auzou
** Last update Sun Apr 12 13:49:02 2015 Thibaud Auzou
*/

#include "server.h"

int		write_to_client(char *msg, t_fd *client)
{
  return (write(client->_fd, msg, strlen(msg)));
}
