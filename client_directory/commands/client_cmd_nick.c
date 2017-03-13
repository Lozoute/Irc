/*
** client_cmd_nick.c for MyIrc in /home/auzou_t/rendu/PSU_2014_myirc/
** 
** Made by Thibaud Auzou
** Login   <auzou_t@epitech.net>
** 
** Started on  Sun Apr 12 18:46:12 2015 Thibaud Auzou
** Last update Sun Apr 12 18:46:18 2015 Thibaud Auzou
*/

#include "client.h"

int		cmd_nick(t_fd_client *client)
{
  char		*new;
  char		buff[BUFF_SIZE];

  if ((new = strtok(NULL, " ")) == NULL)
    return (print_warning("/nick [nick] --> Nick Is Missing"));
  if (strlen(new) >= NICK_SIZE)
    return (print_warning("Nick Too Long !"));
  strcpy(client->_nick, new);
  if (!client->_connected)
    return (OK);
  sprintf(buff, "NICK %s\r\n", new);
  return (client->_write(buff));
}
