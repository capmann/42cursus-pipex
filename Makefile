SRCS	=	main.c ft_split.c ft_strjoin.c ft_free_all.c ft_redir.c

OBJS	=	${SRCS:.c=.o}

CC		=	gcc

CFLAGS	=	-Wall -Werror -Wextra -g

NAME	=	pipex

.c		:	.o
		${CC} ${CFLAGS} -c $< -o ${<:.c=.o}

${NAME}	:	${OBJS}
		${CC} ${CFLAGS} ${OBJS} -o ${NAME}

all		:	${NAME}

clean	:
			rm -rf ${OBJS}

fclean	:	clean
			rm -rf ${NAME}
			$(MAKE) -C . clean

re	:	fclean all

.PHONY	:	all clean fclean re
			
