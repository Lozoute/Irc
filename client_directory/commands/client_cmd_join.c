/*
** client_cmd_join.c for MyIrc in /home/auzou_t/rendu/PSU_2014_myirc/
** 
** Made by Thibaud Auzou
** Login   <auzou_t@epitech.net>
** 
** Started on  Sun Apr 12 18:47:34 2015 Thibaud Auzou
** Last update Sun Apr 12 18:47:41 2015 Thibaud Auzou
*/

#include "client.h"

int		cmd_join(t_fd_client *client)
{
  char		*chan_name;
  char		buff[BUFF_SIZE];
  char		buffounet[BUFF_SIZE];

  if ((chan_name = strtok(NULL, " ")) == NULL)
    return (print_warning("/join [chan] --> Chan Is Missing"));
  if (chan_name[0] != '#')
    {
      buff[0] = '#';
      strcpy(&(buff[1]), chan_name);
      print_warning("# Was Added Before The Chan Name");
      print_warning("--> Always Add # When You Refer To A Chan");
    }
  else
    strcpy(buff, chan_name);
  if (add_new_chan(buff) == ERROR)
    return (ERROR);
  if (client->_curr_chan == NULL)
    client->_curr_chan = get_chan(buff);
  sprintf(buffounet, "JOIN %s\r\n", buff);
  return (client->_write(buffounet));
}
