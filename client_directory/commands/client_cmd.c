/*
** client_cmd.c for MyIrc in /home/auzou_t/rendu/PSU_2014_myirc/
** 
** Made by Thibaud Auzou
** Login   <auzou_t@epitech.net>
** 
** Started on  Sun Apr 12 18:47:17 2015 Thibaud Auzou
** Last update Sun Apr 12 18:47:23 2015 Thibaud Auzou
*/

#include "client.h"

static int		init_cmds(cmd_function_c *tab)
{
  tab[0] = &cmd_connect;
  tab[1] = &cmd_nick;
  tab[2] = &cmd_list;
  tab[3] = &cmd_join;
  tab[4] = &cmd_part;
  tab[5] = &cmd_users;
  tab[6] = &cmd_msg;
  tab[7] = &cmd_send_file;
  tab[8] = &cmd_accept_file;
  tab[9] = &cmd_switch;
  tab[10] = &cmd_quit;
  return (OK);
}

int			execute_command_input(char *cmd)
{
  static cmd_function_c	commands[NB_CMD_C] = {NULL};
  static char		*cmd_list[NB_CMD_C] = {CMD_CLIENT};
  char			*cmd_name;
  int			i;
  t_fd_client		*client;

  client = get_client_env(GET);
  strcpy(client->_buff, cmd);
  if (commands[0] == NULL)
    init_cmds(commands);
  if (cmd[0] != '/')
    return (send_msg_to_curr_chan(cmd));
  if ((cmd_name = strtok(cmd, " ")) == NULL)
    return (NOK);
  for (i = 0; i < NB_CMD_C; ++i)
    if (!strcmp(cmd_list[i], cmd_name))
      {
	if (!client->_connected && (i > 1 && i < NB_CMD_C - 1))
	  return (print_warning("You Are Not Connected To Any Server"));
	return (commands[i](get_client_env(GET)));
      }
  return (print_warning("Command Not Found."));
}

int			send_msg_to_curr_chan(char *msg)
{
  char			buff[BUFF_SIZE];
  t_fd_client		*client;

  client = get_client_env(GET);
  if (!client->_curr_chan)
    return (print_warning("You Are Not On Any Chan"));
  sprintf(buff, "/msg %s %s", client->_curr_chan->_name, msg);
  sprintf(client->_buff, "/msg %s %s", client->_curr_chan->_name, msg);
  strtok(buff, " ");
  return (cmd_msg(get_client_env(GET)));
}
