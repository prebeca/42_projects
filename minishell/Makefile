# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: user42 <user42@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/11/28 17:48:19 by prebeca           #+#    #+#              #
#    Updated: 2020/10/04 15:09:34 by user42           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	=	minishell

C_DIR	=	src

O_DIR	=	obj

SRCS	=	${wildcard ${C_DIR}/*.c}

OBJS	=	${patsubst ${C_DIR}/%, ${O_DIR}/%, ${SRCS:.c=.o}}

CC		=	clang

CFLAGS	=	-I./inc/ -Wall -Wextra -Werror #-fsanitize=leak

LIBS	=	libft/libft.a

all:		${NAME}

${NAME}:	${OBJS}
			${MAKE} -C libft
			${CC} ${CFLAGS} ${OBJS} ${LIBS} -o ${NAME}

${O_DIR}/%.o : ${C_DIR}/%.c
			@mkdir -p obj
			${CC} ${CFLAGS} -c $< -o $@

.PHONY:		clean fclean re .c.o all

clean:
			rm -rf ${O_DIR}
			${MAKE}	-C libft clean

fclean:		clean
			rm -f ${NAME}
			${MAKE} -C libft fclean

re:			fclean all
