/*
** client_cmd_switch.c for MyIrc in /home/lks/rendu/PSU_2014_myirc
** 
** Made by Thibaud Auzou
** Login   <auzou_t@epitech.net>
** 
** Started on  Sun Apr 12 12:30:33 2015 Thibaud Auzou
** Last update Sun Apr 12 15:25:05 2015 Thibaud Auzou
*/

#include "client.h"

int			cmd_switch(t_fd_client *client)
{
  char			*chan_name;
  t_chan		*chan;

  if ((chan_name = strtok(NULL, " ")) == NULL)
    return (print_warning("/switch [chan] --> Chan Is Missing"));
  if ((chan = get_chan(chan_name)) == NULL)
    return (print_warning("You Have Not Joined This Chan"));
  client->_curr_chan = chan;
  return (OK);
}
