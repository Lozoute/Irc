/*
** server_cmd_accept_file.c for MyIrc in /home/lks/rendu/PSU_2014_myirc/
** 
** Made by Thibaud Auzou
** Login   <auzou_t@epitech.net>
** 
** Started on  Wed Apr  8 15:47:23 2015 Thibaud Auzou
** Last update Sun Apr 12 18:53:04 2015 Thibaud Auzou
*/

#include "server.h"

int			cmd_accept_file(t_fd *client)
{
  printf("CMD ACCEPT FILE : By [%s]\n", client->_client._nick);
  return (OK);
}
