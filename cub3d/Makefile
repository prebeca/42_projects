# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: prebeca <prebeca@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/11/28 17:48:19 by prebeca           #+#    #+#              #
#    Updated: 2020/01/29 13:51:54 by prebeca          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	=	Cub3D

C_DIR	=	src

C_FILES	=	main.c					\
			raycast.c				\
			map_parser.c			\
			get_next_line.c			\
			input_handler.c			\
			move.c					\
			data_flag.c				\
			get_next_line_utils.c	
			
SRCS	=	$(addprefix ${C_DIR}/, ${C_FILES})

OBJS	=	${SRCS:.c=.o}

CC		=	cc

CFLAGS	=	-I./includes/#-Wall -Wextra -Werror

LIBS	=	libft/libft.a #minilibx/libmlx.a

ARG		=	NULL

all:		${NAME}

${NAME}:	${OBJS}
			#${MAKE} -C minilibx
			${MAKE} -C libft bonus
			${CC} ${OBJS} -lmlx -framework OpenGL -framework AppKit ${LIBS} -o ${NAME}

.c.o:
			${CC} ${CFLAGS} -c $< -o $@

.PHONY:		clean fclean re .c.o all

clean:
			rm -f ${OBJS}
			${MAKE} -C minilibx clean
			${MAKE}	-C libft clean

fclean:		clean
			rm -f ${NAME}
			${MAKE} -C libft fclean

re:			fclean all

run:		all
			@echo
			./${NAME} ${ARG}
