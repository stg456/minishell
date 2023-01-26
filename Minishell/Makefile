# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: stgerard <stgerard@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/12/08 19:06:31 by stgerard          #+#    #+#              #
#    Updated: 2023/01/25 15:07:10 by stgerard         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

CC = gcc

CFLAGS = -Wall -Wextra -Werror -g

RM = rm -f

SRCS = minishell.c utils.c parse.c signal.c builtins.c \
../libft/ft_putstr.c ../libft/ft_split.c ../libft/ft_strlen.c \
../libft/ft_strdup.c ../libft/ft_strjoin.c ../libft/ft_isspace.c \
../libft/ft_isascii.c ../libft/ft_strncmp.c

OBJS = ${SRCS:.c=.o}

all: ${NAME}

${NAME}: ${OBJS}
			${CC} -lreadline ${OBJS} ${CFLAGS} -o ${NAME} 
# -g3 -fsanitize=address

clean:
			${RM} ${OBJS}

fclean: clean
			${RM} ${NAME}

re: fclean all

.PHONY: all clean fclean re