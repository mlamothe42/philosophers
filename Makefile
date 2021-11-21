SRCS		=	./srcs/philosophers.c \
				./srcs/ft_init.c \
				./srcs/utils.c \
				./srcs/ft_write.c \
				./srcs/utils_for_threads.c \
				./srcs/threads_routine.c

OBJS		= ${SRCS:.c=.o}

HDRS		= ./includes

NAME		= philosophers

CFLAG		= -Wall -Wextra -Werror

OPTS		= -I ${HDRS}

VALF		= --tool=memcheck --leak-check=full --leak-resolution=high --show-reachable=yes --track-origins=yes --log-file=valgrind_log

all:		${NAME}

.c.o:
			gcc -c ${CFLAG} $< -o ${<:.c=.o} -lpthread

${NAME}:	${OBJS}
			gcc ${OBJS} -o ${NAME} -lpthread

clean:		
			rm -f ${OBJS} ${OBJS_BONUS}

leaks	:
			valgrind ${VALF} ./${NAME} in "ls -l" "wc -l" out
			grep -A1 "valgrind" valgrind_log | grep ${NAME} || echo -n

fclean:		clean
			rm -f ${NAME}

re:			fclean all

.PHONY:		all clean fclean re bonus
