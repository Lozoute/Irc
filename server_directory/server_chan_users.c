/*
** server_chan_users.c for MyIrc in /home/lks/rendu/PSU_2014_myirc/auzou_t/
** 
** Made by Thibaud Auzou
** Login   <auzou_t@epitech.net>
** 
** Started on  Tue Apr  7 20:42:34 2015 Thibaud Auzou
** Last update Sun Apr 12 18:52:00 2015 Thibaud Auzou
*/

#include "server.h"

int		add_user_to_chan(t_fd *user, t_chan *chan)
{
  t_users_list	*new;
  t_users_list	*tmp;

  for (tmp = chan->_users; tmp != NULL; tmp = tmp->_next)
    if (tmp->_user == user)
      return (NOK);
  if ((new = malloc(sizeof(t_users_list))) == NULL)
    return (print_error("ERROR [malloc] :", 1));
  new->_user = user;
  new->_next = chan->_users;
  chan->_users = new;
  return (OK);
}

int		remove_user_from_chan(t_fd *user, t_chan *chan)
{
  t_users_list	*tmp;
  t_users_list	*last;

  last = NULL;
  for (tmp = chan->_users; tmp != NULL; tmp = tmp->_next)
    {
      if (tmp->_user == user)
	{
	  if (!last)
	    chan->_users = tmp->_next;
	  else
	    last->_next = tmp->_next;
	  free(tmp);
	  return (OK);
	}
      last = tmp;
    }
  return (NOK);
}

int		remove_all_users_from_chan(t_chan *chan)
{
  t_users_list	*tmp;
  t_users_list	*last;

  last = NULL;
  for (tmp = chan->_users; tmp != NULL; tmp = last)
    {
      last = tmp->_next;
      free(tmp);
    }
  chan->_users = NULL;
  return (OK);
}

int		send_msg_to_chan(t_chan *chan, t_fd *src, char *msg)
{
  t_users_list	*tmp;
  t_queue	queue;

  queue._next = NULL;
  strcpy(queue._msg._msg, msg);
  for (tmp = chan->_users; tmp != NULL; tmp = tmp->_next)
    {
      if (tmp->_user != src)
	{
	  queue._msg._dest = tmp->_user;
	  if (add_t_queue_to_queue(&queue) == ERROR)
	    return (ERROR);
	}
    }
  return (OK);
}
