# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: user42 <user42@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/11/28 17:48:19 by prebeca           #+#    #+#              #
#    Updated: 2020/06/17 11:54:02 by user42           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	=	Cub3D

C_DIR	=	src

C_FILES	=	bmp.c					\
			data.c					\
			draw.c					\
			draw_utils.c			\
			draw_sprites.c			\
			draw_sprites_utils.c	\
			get_next_line.c			\
			get_next_line_utils.c	\
			main.c					\
			movement.c				\
			parsing.c				\
			parsing_data.c			\
			parsing_data_utils.c	\
			parsing_map.c			\
			parsing_map_utils.c		\
			setup_window.c			\
			setup_window_utils.c	\
			utils.c
			
SRCS	=	$(addprefix ${C_DIR}/, ${C_FILES})

OBJS	=	${SRCS:.c=.o}

CC		=	clang

CFLAGS	=	-I./inc/ -Wall -Wextra -Werror -fsanitize=address

LIBS	=	libft/libft.a minilibx-linux/libmlx_Linux.a

ARG		=	NULL

all:		${NAME}

${NAME}:	${OBJS}
			${MAKE} -C libft bonus
			${MAKE} -C minilibx-linux
			${CC} ${CFLAGS} ${OBJS} -lX11 -lXext -lbsd -lm ${LIBS} -o ${NAME}

.c.o:
			${CC} ${CFLAGS} -c $< -o $@

.PHONY:		clean fclean re .c.o all run

clean:
			rm -f ${OBJS}
			${MAKE}	-C libft clean
			${MAKE} -C minilibx-linux clean

fclean:		clean
			rm -f ${NAME}
			${MAKE} -C libft fclean

re:			fclean all