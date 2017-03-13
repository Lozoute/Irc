/*
** client_cmd_quit.c for MyIrc in /home/auzou_t/rendu/PSU_2014_myirc/
** 
** Made by Thibaud Auzou
** Login   <auzou_t@epitech.net>
** 
** Started on  Sun Apr 12 18:45:56 2015 Thibaud Auzou
** Last update Sun Apr 12 18:46:04 2015 Thibaud Auzou
*/

#include "client.h"

int		cmd_quit(t_fd_client *client)
{
  client_running(1);
  return (client->_fd);
}
