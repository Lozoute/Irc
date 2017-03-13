/*
** myirc.h for MyIrc in /home/lks/rendu/PSU_2014_myirc/auzou_t
** 
** Made by Thibaud Auzou
** Login   <auzou_t@epitech.net>
** 
** Started on  Mon Apr  6 13:59:18 2015 Thibaud Auzou
** Last update Sun Apr 12 18:39:26 2015 Thibaud Auzou
*/

#ifndef MYIRC_H_
# define MYIRC_H_

/*
** LibC
*/
# include <unistd.h>
# include <string.h>
# include <stdlib.h>
# include <errno.h>
# include <stdio.h>
# include <signal.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <time.h>
# include <ctype.h>
# include <dirent.h>
# include <stdarg.h>
# include <sys/types.h>
# include <sys/ioctl.h>
# include "codes.h"

/*
** Network - TCP/IP
*/
# include <sys/socket.h>
# include <netdb.h>
# include <netinet/in.h>
# include <netinet/ip.h>
# include <netinet/tcp.h>
# include <arpa/inet.h>

/*
** Return Codes
*/
# define ERROR			-1
# define OK			1
# define NOK			0

/*
** TCP Informations
*/
# define PROTO_NAME		"TCP"

/*
** Wrappers Actions Codes
*/
# define GET			1
# define DESTROY		0
# define CLEAN			2

/*
** Misc
*/
# define BUFF_SIZE		1024
# define MAX_FD			20
# define MAX_USERS		20
# define MAX_CHAN		10
# define CHAN_SIZE		200
# define NICK_SIZE		10
# define MAX_USER_CHAN		200
# define STDIN			0

/*
** Commands
*/
# define NB_CMD			11
# define CMD1			"NICK", "USER",
# define CMD2			"PASS",
# define CMD3			"LIST", "JOIN", "PART", "NAMES",
# define CMD4			"PRIVMSG", "SENDFILE", "ACCEPTFILE", "QUIT"
# define CMDS			CMD1 CMD2 CMD3 CMD4

# define CMD5			,"SERVER"
# define CMDS2			CMD1 CMD3 CMD4 CMD5

# define NB_CMD_C		11
# define CMD_C1			"/server", "/nick", "/list", "/join", "/part",
# define CMD_C2			"/users", "/msg", "/send_file", "/accept_file",
# define CMD_C3			"/switch", "/quit"
# define CMD_CLIENT		CMD_C1 CMD_C2 CMD_C3

/*
** Why Not
*/
typedef struct			s_fd t_fd;
typedef struct			s_fd_client t_fd_client;
typedef struct sockaddr_in	t_sockaddr;
typedef struct timeval		t_timeval;
typedef int(*read_function)	(t_fd *);
typedef int(*write_function)	(char *, t_fd *);
typedef int(*cmd_function)	(t_fd *);
typedef int(*read_function_c)	(int);
typedef int(*write_function_c)	(char *);
typedef int(*cmd_function_c)	(t_fd_client *);
typedef struct protoent		t_protoent;

typedef enum			e_fd_state
  {
    FREE,
    CLIENT,
    SERVER,
  }				t_fd_state;

/*
** Chan Structures
*/
typedef struct			s_users_list
{
  t_fd				*_user;
  struct s_users_list		*_next;
}				t_users_list;

typedef struct			s_chan
{
  char				_name[CHAN_SIZE];
  char				_topic[BUFF_SIZE];
  int				_size;
  t_users_list			*_users;
}				t_chan;

typedef struct			s_chan_list
{
  t_chan			_chan;
  struct s_chan_list		*_next;
}				t_chan_list;

/*
** User / Client Structures
*/
typedef struct			s_client
{
  char				_nick[NICK_SIZE];
  int				_connected;
  int				_welcomed;
  t_chan			*_chans[MAX_CHAN];
}				t_client;

typedef struct			s_fd
{
  int				_fd;
  char				_buff[BUFF_SIZE];
  int				_pos;
  int				_clean;
  t_fd_state			_state;
  read_function			_read;
  write_function		_write;
  t_client			_client;
}				t_fd;

typedef struct			s_fd_client
{
  int				_fd;
  char				_nick[NICK_SIZE];
  char				_buff[BUFF_SIZE];
  read_function_c		_read;
  write_function_c		_write;
  int				_connected;
  t_chan			*_curr_chan;
}				t_fd_client;

/*
** Message / Queue Structure
*/
typedef struct			s_msg
{
  char				_msg[BUFF_SIZE];
  t_fd				*_dest;
}				t_msg;

typedef struct			s_queue
{
  t_msg				_msg;
  struct s_queue		*_next;
}				t_queue;

/*
** Common Functions
*/
int				print_error(const char *, int);
int				print_warning(const char *);

#endif /* !MYIRC_H_ */
