/*
** client_cmd_list.c for MyIrc in /home/auzou_t/rendu/PSU_2014_myirc/
** 
** Made by Thibaud Auzou
** Login   <auzou_t@epitech.net>
** 
** Started on  Sun Apr 12 18:46:33 2015 Thibaud Auzou
** Last update Sun Apr 12 18:46:39 2015 Thibaud Auzou
*/

#include "client.h"

int		cmd_list(t_fd_client *client)
{
  char		*search;
  char		buff[BUFF_SIZE];

  search = strtok(NULL, " ");
  sprintf(buff, "LIST %s\r\n", (search) ? (search) : (""));
  return (client->_write(buff));
}
