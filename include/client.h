/*
** client.h for myirc in /home/montre_n/tech2/c/PSU_2014_myirc/nico
** 
** Made by nicolas montredon
** Login   <montre_n@epitech.net>
** 
** Started on  Thu Apr  9 14:29:58 2015 nicolas montredon
** Last update Tue Apr 14 19:51:32 2015 nicolas montredon
*/

#ifndef CLIENT_H_
# define CLIENT_H_

# include "myirc.h"

/*
** Initialisation Client Launcher (/client_directory/client.c)
*/
int			launch_client(void);
int			client_run(void);

/*
** Client Environment (/client_directory/client_env.c)
*/
t_fd_client		*get_client_env(int);

/*
** Client States
*/
int			client_running(int);
void			shutdown_client(int);

/*
** read_function
*/
int			client_read(int);
int			client_write_to_serv(char *);
int			read_from_user(void);
int			read_from_server(int);

/*
** client Buffer
*/
char			*buffer(void);

/*
** commands handler
*/
int			execute_command_input(char *);
int			send_msg_to_curr_chan(char *);
int			connect_client(char *, int);

/*
** commands
*/
int			cmd_msg(t_fd_client *);
int			cmd_nick(t_fd_client *);
int			cmd_list(t_fd_client *);
int			cmd_join(t_fd_client *);
int			cmd_part(t_fd_client *);
int			cmd_names(t_fd_client *);
int			cmd_send_file(t_fd_client *);
int			cmd_accept_file(t_fd_client *);
int			cmd_quit(t_fd_client *);
int			cmd_connect(t_fd_client *);
int			cmd_users(t_fd_client *);
int			cmd_switch(t_fd_client *);

/*
** Check information ip (client_directory/client_ipvalid.c)
*/
int			isip_valid(char *);

/*
** Chan Functions (client_directory/client_chan.c)
*/
t_chan_list		**chan_list(int);
t_chan_list		*get_chan_list(void);
t_chan			*get_chan(char *);
int			add_new_chan(char *);
int			remove_chan(char *);

#endif /* !CLIENT_H_ */
