/*
** server.h for MyIrc in /home/auzou_t/rendu/PSU_2014_myirc/include
** 
** Made by Thibaud Auzou
** Login   <auzou_t@epitech.net>
** 
** Started on  Sun Apr 12 18:38:01 2015 Thibaud Auzou
** Last update Sun Apr 12 18:38:14 2015 Thibaud Auzou
*/

#ifndef SERVER_H_
# define SERVER_H_

# include "myirc.h"

/*
** Initializing And Running The Server (server_directory/server.c)
*/
int				launch_server(void);
int				monitor_env(t_timeval *, fd_set *, fd_set *);
int				set_fd(t_fd *, fd_set *, fd_set *);
int				msg_queued(t_fd *);

/*
** Sockets Handling (server_directory/server_sockets.c)
*/
int				create_sock_server(int);
int				create_sock_client(t_fd *);

/*
** Fd Environment (server_directory/server_env.c)
*/
t_fd				*get_fd_env(int);
t_fd				*get_client_from_env(int);
t_fd				*get_client_from_env_by_nick(char *);
int				add_fd_to_env(t_fd *);
int				rm_fd_from_env(int);

/*
** Get And Set Server States (server_directory/server_states.c)
*/
int				server_running(int);
void				shutdown_server(int);

/*
** Read Functions (server_directory/server_read_functions.c)
*/
int				read_from_client(t_fd *);

/*
** Write Functions (server_directory/server_write_functions.c)
*/
int				write_to_client(char *, t_fd *);

/*
** Server Buffer (server_directory/server_buffer.c)
*/
char				*buffer(void);

/*
** Server IDLE Mode (server_directory/server_idle.c)
*/
int				start_idle(void);
int				stop_idle(void);

/*
** Server Chan Operations (server_directory/server_chan.c)
*/
t_chan_list			**chan_list(int);
t_chan_list			*get_chan_list(void);
t_chan				*get_chan(char *);
int				add_new_chan(char *);
int				remove_chan(char *);

/*
** Server Chan Users Operations (server_directory/server_chan_users.c))
*/
int				add_user_to_chan(t_fd *, t_chan *);
int				remove_user_from_chan(t_fd *, t_chan *);
int				remove_all_users_from_chan(t_chan *);
int				send_msg_to_chan(t_chan *, t_fd *, char *);

/*
** Message Queue (server_directory/server_msg.c)
*/
t_queue				**get_queue(int);
int				add_msg_to_queue(t_fd *, char *, ...);
int				add_t_queue_to_queue(t_queue *);
int				remove_msg_from_queue(t_queue *);
int				try_to_send_all_msg(fd_set *);

/*
** Message Queue - Users (server_directory/server_msg_users.c)
*/
int				remove_all_msg_to_user(t_fd *);

/*
** Commands Handling (server_directory/commands/server_cmd.c)
*/
int				execute_command(t_fd *);

/*
** Command List (server_directory/commands/server_cmd_<name>.c)
*/
int				cmd_nick(t_fd *);
int				cmd_user(t_fd *);
int				cmd_pass(t_fd *);
int				cmd_list(t_fd *);
int				cmd_join(t_fd *);
int				cmd_part(t_fd *);
int				cmd_names(t_fd *);
int				cmd_privmsg(t_fd *);
int				cmd_send_file(t_fd *);
int				cmd_accept_file(t_fd *);
int				cmd_quit(t_fd *);
int				send_welcome_msg(t_fd *);
int				add_chan_to_user(t_chan *, t_fd *);
int				already_in_chan(t_chan *, t_fd *);
int				remove_chan_from_user(t_chan *, t_fd *);

#endif /* !SERVER_H_ */
