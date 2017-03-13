/*
** client_cmd_users.c for MyIrc in /home/auzou_t/rendu/PSU_2014_myirc/
** 
** Made by Thibaud Auzou
** Login   <auzou_t@epitech.net>
** 
** Started on  Sun Apr 12 18:45:35 2015 Thibaud Auzou
** Last update Sun Apr 12 18:45:41 2015 Thibaud Auzou
*/

#include "client.h"

int			cmd_users(t_fd_client *client)
{
  char			buff[BUFF_SIZE];

  if (!client->_curr_chan)
    return (print_warning("You Are Not On Any Chan"));
  sprintf(buff, "NAMES %s\r\n", client->_curr_chan->_name);
  return (client->_write(buff));
}
