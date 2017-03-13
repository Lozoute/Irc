/*
** server_cmd_send_file.c for MyIrc in /home/lks/rendu/PSU_2014_myirc/auzou_t/
** 
** Made by Thibaud Auzou
** Login   <auzou_t@epitech.net>
** 
** Started on  Wed Apr  8 15:46:59 2015 Thibaud Auzou
** Last update Sun Apr 12 18:52:40 2015 Thibaud Auzou
*/

#include "server.h"

int			cmd_send_file(t_fd *client)
{
  printf("CMD SEND FILE : By [%s]\n", client->_client._nick);
  return (OK);
}
