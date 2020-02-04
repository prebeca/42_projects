# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: prebeca <prebeca@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/11/28 17:48:19 by prebeca           #+#    #+#              #
#    Updated: 2020/02/04 05:06:01 by prebeca          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	=	Cub3D

C_DIR	=	src

C_FILES	=	main.c					\
			get_next_line.c			\
			get_next_line_utils.c	\
			init_data.c				\
			map_parser.c			\
			mlx_hook.c				\
			move.c					\
			map_checker.c			\
			raycast.c
			
SRCS	=	$(addprefix ${C_DIR}/, ${C_FILES})

OBJS	=	${SRCS:.c=.o}

CC		=	cc

CFLAGS	=	-I./inc/ #-Wall -Wextra -Werror

LIBS	=	libft/libft.a

ARG		=	NULL

all:		${NAME}

${NAME}:	${OBJS}
			${MAKE} -C libft bonus
			${CC} ${OBJS} -lmlx -framework OpenGL -framework AppKit ${LIBS} -o ${NAME}

.c.o:
			${CC} ${CFLAGS} -c $< -o $@

.PHONY:		clean fclean re .c.o all run

clean:
			rm -f ${OBJS}
			${MAKE}	-C libft clean

fclean:		clean
			rm -f ${NAME}
			${MAKE} -C libft fclean

re:			fclean all

run:		all
			@echo
			./${NAME} ${ARG}
