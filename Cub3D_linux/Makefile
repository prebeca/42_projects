# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: user42 <user42@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/11/28 17:48:19 by prebeca           #+#    #+#              #
#    Updated: 2020/09/11 16:50:00 by user42           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	=	Cub3D

C_DIR	=	src

O_DIR	=	obj

C_FILES	=	${wildcard ${C_DIR}/*.c}

OBJS	=	${patsubst ${C_DIR}/%, ${O_DIR}/%, ${C_FILES:.c=.o}}

CC		=	clang

CFLAGS	=	-I./inc/ -Wall -Wextra -Werror #-fsanitize=leak

LIBS	=	libft/libft.a minilibx-linux/libmlx_Linux.a

all:		${NAME}

${NAME}:	${OBJS}
			${MAKE} -C libft bonus
			${MAKE} -C minilibx-linux
			${CC} ${CFLAGS} ${OBJS} -lX11 -lXext -lbsd -lm ${LIBS} -o ${NAME}

${O_DIR}/%.o : ${C_DIR}/%.c
			@mkdir -p obj
			${CC} ${CFLAGS} -c $< -o $@

.PHONY:		clean fclean re .c.o all run

clean:
			rm -rf ${O_DIR}
			${MAKE}	-C libft clean
			${MAKE} -C minilibx-linux clean

fclean:		clean
			rm -f ${NAME}
			${MAKE} -C libft fclean

re:			fclean all
