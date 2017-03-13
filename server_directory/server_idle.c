/*
** server_idle.c for MyIrc in /home/lks/rendu/PSU_2014_myirc/auzou_t/
** 
** Made by Thibaud Auzou
** Login   <auzou_t@epitech.net>
** 
** Started on  Tue Apr  7 19:04:20 2015 Thibaud Auzou
** Last update Sun Apr 12 18:52:05 2015 Thibaud Auzou
*/

#include "server.h"

static int		idle(int action)
{
  static int		_idle = 0;

  if (action == 1)
    _idle = 1;
  else if (action == 0)
    _idle = 0;
  return (_idle);
}

int			start_idle(void)
{
  if (idle(2) == 0)
    {
      printf("\r\x1b[1;33mServer IDLE.....\x1b[0m");
      fflush(stdout);
      idle(1);
    }
  return (OK);
}

int			stop_idle(void)
{
  if (idle(2) == 1)
    {
      printf("\r\x1b[1;31mTreating Data...\x1b[0m");
      fflush(stdout);
      idle(0);
    }
  return (OK);
}
