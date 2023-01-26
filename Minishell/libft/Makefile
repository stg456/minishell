# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: stgerard <stgerard@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/02/25 12:01:50 by stgerard          #+#    #+#              #
#    Updated: 2023/01/25 15:03:26 by stgerard         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS		=  ft_isalpha.c	ft_memchr.c	ft_putchar_fd.c	ft_strchr.c \
ft_strlcpy.c ft_strrchr.c ft_atoi.c	ft_isascii.c ft_memcmp.c ft_putendl_fd.c \
ft_strdup.c	ft_strlen.c	ft_strtrim.c ft_bzero.c	ft_isdigit.c ft_memcpy.c \
ft_putnbr_fd.c	ft_striteri.c	ft_strmapi.c	ft_substr.c ft_calloc.c \
ft_isprint.c ft_memmove.c ft_putstr_fd.c ft_strjoin.c ft_strncmp.c \
ft_tolower.c ft_isalnum.c ft_itoa.c	ft_memset.c	ft_split.c ft_strlcat.c \
ft_strnstr.c ft_toupper.c ft_islonglong.c ft_intlen.c ft_dectobin.c \
ft_putstr.c ft_strstr.c \
ft_printf.c ft_printf_utils.c ft_printf_utils2.c \
ft_printf_utils3.c ft_printf_utils4.c get_next_line.c ft_arr_freer.c

SRCSB		=  ft_lstnew_bonus.c ft_lstadd_front_bonus.c ft_lstsize_bonus.c \
ft_lstlast_bonus.c ft_lstadd_back_bonus.c ft_lstdelone_bonus.c \
ft_lstclear_bonus.c ft_lstiter_bonus.c ft_lstmap_bonus.c

CC			= gcc
CFLAGS		= -Wall -Werror -Wextra
RM			= rm -f
OBJS		= ${SRCS:.c=.o}
OBJSB		= ${SRCSB:.c=.o}
NAME		= libft.a

.c.o:
				${CC} ${CFLAGS} -I. -c $< -o ${<:.c=.o}

${NAME}: ${OBJS}
				ar rcs ${NAME} ${OBJS}

bonus: ${NAME} ${OBJS} ${OBJSB}
				ar rcs ${NAME} ${OBJS} ${OBJSB}

all: ${NAME}

clean:
				${RM} ${OBJS} ${OBJSB}

fclean:		clean
				${RM} ${NAME} ${OBJSB}

re:			fclean all

.PHONY:		all clean fclean re bonus

