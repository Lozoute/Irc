/*
** client_chan.c for MyIrc in /home/auzou_t/rendu/PSU_2014_myirc/
** 
** Made by Thibaud Auzou
** Login   <auzou_t@epitech.net>
** 
** Started on  Sun Apr 12 18:41:50 2015 Thibaud Auzou
** Last update Sun Apr 12 18:41:56 2015 Thibaud Auzou
*/

#include "client.h"

t_chan_list		**chan_list(int action)
{
  static t_chan_list	*begin = NULL;
  t_chan_list		*tmp;

  if (action == DESTROY && begin != NULL)
    {
      for (tmp = NULL; begin != NULL; begin = tmp)
	{
	  tmp = begin->_next;
	  free(begin);
	}
      begin = NULL;
    }
  return (&begin);
}

t_chan_list		*get_chan_list(void)
{
  return (*(chan_list(GET)));
}

t_chan			*get_chan(char *name)
{
  t_chan_list		*tmp;

  for (tmp = get_chan_list(); tmp != NULL; tmp = tmp->_next)
    if (!strcmp(name, tmp->_chan._name))
      return (&(tmp->_chan));
  return (NULL);
}

int			add_new_chan(char *name)
{
  t_chan_list		*tmp;
  t_chan_list		*last;

  last = get_chan_list();
  for (tmp = get_chan_list(); tmp != NULL; tmp = tmp->_next)
    {
      if (!strcmp(name, tmp->_chan._name))
	return (NOK);
      last = tmp;
    }
  if ((tmp = malloc(sizeof(t_chan_list))) == NULL)
    return (print_error("ERROR [malloc] :", 1));
  strcpy(tmp->_chan._name, "#");
  strcat(tmp->_chan._name, (name[0] == '#') ? (&(name[1])) : (name));
  strcpy(tmp->_chan._topic, "No Special Topic");
  tmp->_chan._users = NULL;
  tmp->_next = NULL;
  tmp->_chan._size = 0;
  if (last)
    last->_next = tmp;
  else
    *(chan_list(GET)) = tmp;
  return (OK);
}

int			remove_chan(char *name)
{
  t_chan_list		*tmp;
  t_chan_list		*last;

  last = NULL;
  for (tmp = get_chan_list(); tmp != NULL; tmp = tmp->_next)
    {
      if (!strcmp(name, tmp->_chan._name))
	{
	  if (!last)
	    *(chan_list(GET)) = tmp->_next;
	  else
	    last->_next = tmp->_next;
	  free(tmp);
	  return (OK);
	}
      last = tmp;
    }
  return (NOK);
}
