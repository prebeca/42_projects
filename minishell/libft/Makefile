
NAME	=	libft.a

C_DIR	=	src

O_DIR	=	obj

SRCS	=	${wildcard ${C_DIR}/*.c}

OBJS	=	${patsubst ${C_DIR}/%, ${O_DIR}/%, ${SRCS:.c=.o}}

CC		=	clang

CFLAGS	=	-I. -Wall -Wextra -Werror #fsanitize=address

all:		${NAME}

$(NAME):	${OBJS}
			ar rc ${NAME} ${OBJS}


${O_DIR}/%.o : ${C_DIR}/%.c
			@mkdir -p obj
			${CC} ${CFLAGS} -c $< -o $@

.PHONY:		clean fclean re bonus .c.o all

clean:
			rm -f ${OBJS}

fclean:		clean
			rm -f ${NAME}

re:			fclean all
