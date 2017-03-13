/*
** server_cmd.c for MyIrc in /home/lks/rendu/PSU_2014_myirc/auzou_t/
** 
** Made by Thibaud Auzou
** Login   <auzou_t@epitech.net>
** 
** Started on  Wed Apr  8 11:49:48 2015 Thibaud Auzou
** Last update Sun Apr 12 18:53:10 2015 Thibaud Auzou
*/

#include "server.h"

static int		init_cmds(cmd_function *tab)
{
  static int		first = 1;

  if (first)
    first = !first;
  else
    return (OK);
  tab[0] = &cmd_nick;
  tab[1] = &cmd_user;
  tab[2] = &cmd_pass;
  tab[3] = &cmd_list;
  tab[4] = &cmd_join;
  tab[5] = &cmd_part;
  tab[6] = &cmd_names;
  tab[7] = &cmd_privmsg;
  tab[8] = &cmd_send_file;
  tab[9] = &cmd_accept_file;
  tab[10] = &cmd_quit;
  return (OK);
}

int			execute_command(t_fd *client)
{
  static cmd_function	commands[NB_CMD] = {NULL};
  static char		*cmd_list[NB_CMD] = {CMDS};
  char			save[BUFF_SIZE];
  char			*cmd_name;
  int			i;

  init_cmds(commands);
  strcpy(save, client->_buff);
  if ((cmd_name = strtok(save, " ")) == NULL)
    return (NOK);
  for (i = 0; cmd_name[i]; ++i)
    cmd_name[i] = toupper(cmd_name[i]);
  for (i = 0; i < NB_CMD; ++i)
    {
      if (!strcmp(cmd_list[i], cmd_name))
	{
	  if (i > 2 && i != NB_CMD - 1 && !client->_client._welcomed)
	    return (add_msg_to_queue(client, "451 %s\r\n", E_451));
	  else
	    return (commands[i](client));
	}
    }
  if (strlen(cmd_name) > 50)
    cmd_name[50] = 0;
  return (add_msg_to_queue(client, "421 %s %s\r\n", cmd_name, E_421));
}
