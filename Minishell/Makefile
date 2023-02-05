# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: stgerard <stgerard@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/12/08 19:06:31 by stgerard          #+#    #+#              #
#    Updated: 2023/02/05 18:11:58 by stgerard         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

 #	NAME :
NAME	:= 	minishell
#	FILE :
SRC_DIR	:= 	src

SRCS	:=	builtins.c				\
			minishell.c				\
			parse.c					\
			quote.c					\
			signal.c				\
			utils.c					\
			linked_list.c			\


SRCS := 	$(SRCS:%=$(SRC_DIR)/%)

#	COMPILATION:
CC := 		@gcc
CFLAGS := 	-Wall -Werror -Wextra
LIBS :=		-Llibft -lft
DANGER := -fsanitize=address

#	STATIC LIB CREATION:
AR :=		@ar
ARFLAG :=	-rcs

#	BUILD:
OBJS_DIR := .build
OBJS = $(SRCS:$(SRC_DIR)/%.c=$(OBJS_DIR)/%.o)
LIBFILE := libft

#	TOOLS:

RM	:= @rm -rf
DUP_DIR = @mkdir -p $(@D)
CREATE_DIR = [ ! -d $(OBJS_DIR) ] && mkdir $(OBJS_DIR)
ALLOBJS = $(OBJS_DIR)/%.o

#	COMMAND:

all : $(NAME)

.create.build :
	$(CREATE_DIR)
	$(CLONE_LIB)

$(OBJS_DIR)/%.o : $(SRC_DIR)/%.c
	@make -sC libft
	$(DUP_DIR)
	$(CC) $(CFLAGS) -c -o $@ $<
	@echo "\033[1A\033[0J\033[32;1m\rMinishell compilation >>\033[0m\033[30;1m $@\033[0m"

$(NAME) : $(OBJS)
	$(CC) -o $(NAME) $(OBJS) $(LIBS) -lreadline -L ${HOME}/.brew/opt/readline/lib -I ${HOME}/.brew/opt/readline/include
clean :/
	@make clean -sC libft
	$(RM) $(OBJS_DIR)

fclean : clean
	@make fclean -sC libft
	$(RM) $(NAME)

re : fclean all