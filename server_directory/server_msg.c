/*
** server_msg.c for MyIrc in /home/lks/rendu/PSU_2014_myirc/auzou_t/
** 
** Made by Thibaud Auzou
** Login   <auzou_t@epitech.net>
** 
** Started on  Wed Apr  8 19:52:24 2015 Thibaud Auzou
** Last update Sun Apr 12 18:51:28 2015 Thibaud Auzou
*/

#include "server.h"

t_queue				**get_queue(int action)
{
  static t_queue		*begin = NULL;
  t_queue			*last;

  if (action == DESTROY && begin != NULL)
    {
      for (last = NULL; begin != NULL; begin = last)
	{
	  last = begin->_next;
	  free(begin);
	}
      begin = NULL;
    }
  return (&begin);
}

int				add_msg_to_queue(t_fd *dest, char *msg, ...)
{
  t_queue			*new;
  t_queue			*tmp;
  va_list			ap;
  char				buff[BUFF_SIZE];

  va_start(ap, msg);
  vsprintf(buff, msg, ap);
  va_end(ap);
  if ((new = malloc(sizeof(t_queue))) == NULL)
    return (print_error("ERROR [malloc] :", 1));
  new->_next = NULL;
  new->_msg._dest = dest;
  strcpy(new->_msg._msg, buff);
  for (tmp = *(get_queue(GET)); tmp && tmp->_next; tmp = tmp->_next);
  if (!tmp)
    *(get_queue(GET)) = new;
  else
    tmp->_next = new;
  return (OK);
}

int				add_t_queue_to_queue(t_queue *elem)
{
  t_queue			*new;
  t_queue			*tmp;

  if ((new = malloc(sizeof(t_queue))) == NULL)
    return (print_error("ERROR [malloc] :", 1));
  memcpy(new, elem, sizeof(t_queue));
  new->_next = NULL;
  for (tmp = *(get_queue(GET)); tmp && tmp->_next; tmp = tmp->_next);
  if (!tmp)
    *(get_queue(GET)) = new;
  else
    tmp->_next = new;
  return (OK);
}

int				remove_msg_from_queue(t_queue *elem)
{
  t_queue			*last;
  t_queue			*tmp;

  last = NULL;
  for (tmp = *(get_queue(GET)); tmp != NULL; tmp = tmp->_next)
    {
      if (elem == tmp)
	{
	  if (!last)
	    *(get_queue(GET)) = tmp->_next;
	  else
	    last->_next = tmp->_next;
	  free(tmp);
	  return (OK);
	}
      last = tmp;
    }
  return (NOK);
}

int				try_to_send_all_msg(fd_set *write_set)
{
  t_queue			*tmp;
  t_queue			*last;
  int				len;
  int				diff;

  for (tmp = *(get_queue(GET)); tmp != NULL; tmp = last)
    {
      last = tmp->_next;
      if (FD_ISSET(tmp->_msg._dest->_fd, write_set))
	{
	  len = strlen(tmp->_msg._msg);
	  diff = (tmp->_msg._dest->_write)(tmp->_msg._msg, tmp->_msg._dest);
	  if (diff == -1)
	    return (ERROR);
	  diff = len - diff;
	  if (diff == 0)
	    remove_msg_from_queue(tmp);
	  else
	    strcpy(tmp->_msg._msg, tmp->_msg._msg + (len - diff));
	}
    }
  return (OK);
}
