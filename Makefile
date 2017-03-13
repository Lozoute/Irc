##
## Makefile for MyIrc in /home/auzou_t/rendu/PSU_2014_myirc
## 
## Made by Thibaud Auzou
## Login   <auzou_t@epitech.net>
## 
## Started on  Sun Apr 12 18:32:28 2015 Thibaud Auzou
## Last update Sun Apr 12 18:32:47 2015 Thibaud Auzou
##

CC		= gcc

RM		= rm -f

CFLAGS		+= -Wextra -Wall
CFLAGS		+=
CFLAGS		+= -I./include/ -I../include/

LDFLAGS		=


##
## Common Files
##
COMMON_SRC	= common_functions/print_error.c \
		  common_functions/print_warning.c

##
## Server
##
SERVER_NAME	= server

SERVER_SRCS	= server_directory/server.c \
		  server_directory/server_sockets.c \
		  server_directory/server_env.c \
		  server_directory/server_read_functions.c \
		  server_directory/server_write_functions.c \
		  server_directory/server_buffer.c \
		  server_directory/server_states.c \
		  server_directory/server_idle.c \
		  server_directory/server_chan.c \
		  server_directory/server_chan_users.c \
		  server_directory/server_msg.c \
		  server_directory/server_msg_users.c \
		  server_directory/commands/server_cmd.c \
		  server_directory/commands/server_cmd_nick.c \
		  server_directory/commands/server_cmd_user.c \
		  server_directory/commands/server_cmd_pass.c \
		  server_directory/commands/server_cmd_join.c \
		  server_directory/commands/server_cmd_part.c \
		  server_directory/commands/server_cmd_list.c \
		  server_directory/commands/server_cmd_names.c \
		  server_directory/commands/server_cmd_privmsg.c \
		  server_directory/commands/server_cmd_send_file.c \
		  server_directory/commands/server_cmd_accept_file.c \
		  server_directory/commands/server_cmd_quit.c \
		  $(COMMON_SRC)

SERVER_OBJS	= $(SERVER_SRCS:.c=.o)


##
## Client
##
CLIENT_NAME	= client

CLIENT_SRCS	= client_directory/client.c \
                  client_directory/client_ipvalid.c \
                  client_directory/client_states.c \
                  client_directory/client_env.c \
                  client_directory/client_read_functions.c \
                  client_directory/client_write_functions.c \
                  client_directory/client_buffer.c \
                  client_directory/client_chan.c \
                  client_directory/commands/client_cmd.c \
                  client_directory/commands/client_cmd_msg.c \
                  client_directory/commands/client_cmd_nick.c \
                  client_directory/commands/client_cmd_users.c \
                  client_directory/commands/client_cmd_list.c \
                  client_directory/commands/client_cmd_join.c \
                  client_directory/commands/client_cmd_part.c \
                  client_directory/commands/client_cmd_send_file.c \
                  client_directory/commands/client_cmd_accept_file.c \
		  client_directory/commands/client_cmd_quit.c \
		  client_directory/commands/client_cmd_connect.c \
		  client_directory/commands/client_cmd_switch.c \
		  $(COMMON_SRC)

CLIENT_OBJS	= $(CLIENT_SRCS:.c=.o)



all: $(SERVER_NAME) $(CLIENT_NAME)

$(SERVER_NAME): $(SERVER_OBJS)
		$(CC) $(SERVER_OBJS) -o $(SERVER_NAME) $(LDFLAGS)

$(CLIENT_NAME): $(CLIENT_OBJS)
		$(CC) $(CLIENT_OBJS) -o $(CLIENT_NAME) $(LDFLAGS)

clean:
		$(RM) $(SERVER_OBJS) $(CLIENT_OBJS)

fclean: clean
		$(RM) $(SERVER_NAME) $(CLIENT_NAME)

re: fclean all

.PHONY: all clean fclean re
