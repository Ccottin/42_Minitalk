
SRCS	= utils.c	utils2.c	server.c

SRCC	= utils.c	utils2.c	client.c	client_bin.c

OBJS	= $(SRCS:.c=.o)

OBJC	= $(SRCC:.c=.o)

CC	= gcc

CFLAG	= -Wall -Wextra -Werror -g

all	:	client server

%.o	:	%.c
		$(CC) $(CFLAG) -c $< -o $@

client	:	$(OBJC)
		$(CC) $(OBJC) -o client

server	:	$(OBJS)
		$(CC) $(OBJS) -o server

clean	:
		rm -rf $(OBJS) $(OBJC)

fclean	:	clean
		rm -rf client server

re	:	fclean all

.PHONY	:	all clean fclean re
