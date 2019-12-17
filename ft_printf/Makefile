# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: prebeca <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/11/28 17:48:19 by prebeca           #+#    #+#              #
#    Updated: 2019/12/10 23:30:57 by prebeca          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	=	libftprintf.a

# *************	#
#	LIBFT SRCS	#
# *************	#

LIB_DIR	=	libft

C_LIBFT	=	ft_memset.c		\
			ft_bzero.c		\
			ft_memcpy.c		\
			ft_memccpy.c	\
			ft_memmove.c 	\
			ft_memchr.c		\
			ft_memcmp.c		\
			ft_strlen.c		\
			ft_isalpha.c	\
			ft_isdigit.c	\
			ft_isalnum.c	\
			ft_isascii.c	\
			ft_isprint.c	\
			ft_toupper.c	\
			ft_tolower.c	\
			ft_strchr.c		\
			ft_strrchr.c	\
			ft_strncmp.c	\
			ft_strlcpy.c	\
			ft_strlcat.c	\
			ft_strnstr.c	\
			ft_atoi.c		\
			ft_strdup.c		\
			ft_calloc.c		\
			ft_substr.c		\
			ft_strjoin.c	\
			ft_strtrim.c	\
			ft_split.c		\
			ft_itoa.c		\
			ft_strmapi.c	\
			ft_putchar_fd.c	\
			ft_putstr_fd.c	\
			ft_putendl_fd.c	\
			ft_putnbr_fd.c

LIBFT	=	$(addprefix ${LIB_DIR}/, ${C_LIBFT})

# *************	#
#	PRINTF SRCS	#
# *************	#

C_DIR	=	srcs

C_FILES	=	ft_printf.c		\
			printf_parser.c	\
			handle_var.c	\
			ft_itoa_base.c	\
			conv_spe_c.c	\
			conv_spe_s.c	\
			conv_spe_d.c	\
			conv_spe_p.c	\
			conv_spe_u.c	\
			conv_spe_x.c	\
			conv_spe_prct.c

SRCS	=	$(addprefix ${C_DIR}/, ${C_FILES})

# *************	#
#	OBJS		#
# *************	#

OBJS	=	${SRCS:.c=.o} ${LIBFT:.c=.o}

# *************	#
#	MAKE LIB	#
# *************	#

CC		=	gcc

CFLAGS	=	-I./includes/ -Wall -Wextra -Werror

all:		${NAME}

${NAME}:	${OBJS}
			ar rc ${NAME} ${OBJS}

.c.o:
			${CC} ${CFLAGS} -c $< -o $@

.PHONY:		clean fclean re .c.o all

clean:
			rm -f ${OBJS}

fclean:		clean
			rm -f ${NAME}

re:			fclean all
