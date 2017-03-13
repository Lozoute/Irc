/*
** client_cmd_part.c for MyIrc in /home/auzou_t/rendu/PSU_2014_myirc/
** 
** Made by Thibaud Auzou
** Login   <auzou_t@epitech.net>
** 
** Started on  Sun Apr 12 18:48:05 2015 Thibaud Auzou
** Last update Sun Apr 12 18:48:11 2015 Thibaud Auzou
*/

#include "client.h"

int		cmd_part(t_fd_client *client)
{
  char		*chan_name;
  char		buff[BUFF_SIZE];

  if ((chan_name = strtok(NULL, " ")) == NULL)
    return (print_warning("/part [chan] --> Chan Is Missing"));
  sprintf(buff, "PART %s\r\n", chan_name);
  if (client->_curr_chan && !strcmp(client->_curr_chan->_name, chan_name))
    client->_curr_chan = NULL;
  remove_chan(chan_name);
  return (client->_write(buff));
}
