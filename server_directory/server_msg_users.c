/*
** server_msg_users.c for MyIrc in /home/lks/rendu/PSU_2014_myirc/auzou_t/
** 
** Made by Thibaud Auzou
** Login   <auzou_t@epitech.net>
** 
** Started on  Fri Apr 10 16:49:45 2015 Thibaud Auzou
** Last update Sun Apr 12 18:52:10 2015 Thibaud Auzou
*/

#include "server.h"

int			remove_all_msg_to_user(t_fd *user)
{
  t_queue			*tmp;
  t_queue			*last;

  for (tmp = *(get_queue(GET)); tmp != NULL; tmp = last)
    {
      last = tmp->_next;
      if (tmp->_msg._dest == user)
	remove_msg_from_queue(tmp);
    }
  return (OK);
}
