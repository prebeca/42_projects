# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: user42 <user42@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/11/28 17:48:19 by prebeca           #+#    #+#              #
#    Updated: 2020/10/01 13:16:46 by user42           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	=	libasm.a
TEST	=	test

C_FILES	=	${wildcard *.c}

S_DIR	=	src
S_FILES	=	${wildcard ${S_DIR}/*.s}
S_OBJS	=	${patsubst ${S_DIR}/%, ${O_DIR}/%, ${S_FILES:.s=.o}}

O_DIR	=	obj

NASM	=	nasm
NASMFLAGS	= -f elf64

CC		=	clang
CFLAGS	=	-Wall -Werror -Wextra #-fsanitize=address

all:		${NAME}

${NAME}:	${S_OBJS}
			ar rc ${NAME} ${S_OBJS}

${O_DIR}/%.o : ${S_DIR}/%.s
			@mkdir -p ${O_DIR}
			${NASM} ${NASMFLAGS} $< -o $@

test:		${NAME}
			${CC} ${CFLAGS} ${C_FILES} libasm.a -o ${TEST}

.PHONY:		clean fclean re .c.o all test

clean:
			rm -rf ${O_DIR}

fclean:		clean
			rm -f ${NAME} ${TEST}

re:			fclean all
