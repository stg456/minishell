# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: misimon <misimon@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/12/08 19:06:31 by stgerard          #+#    #+#              #
#    Updated: 2023/03/14 19:01:37 by misimon          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

 #	NAME :
NAME	:= 	minishell
#	FILE :
SRC_DIR	:= 	src

SRCS	:=	exec/builtin/cd.c		\
			exec/builtin/export.c	\
			exec/builtin/env.c		\
			exec/builtin/echo.c		\
			exec/builtin/unset.c	\
			exec/builtin/exit.c		\
			exec/builtin/pwd.c		\
			exec/other_cmd.c		\
			exec/redirection.c		\
			exec/exec_cmd.c			\
			parsing/parse.c			\
			parsing/quote.c			\
			parsing/get_cmd_path.c	\
			parsing/var_parsing.c	\
			parsing/var_utils.c		\
			prompt/prompt_init.c	\
			main.c					\
			signal.c				\
			utils.c					\
			linked_list.c			\


SRCS := 	$(SRCS:%=$(SRC_DIR)/%)

#	COMPILATION:
CC := 		@gcc
CFLAGS := 	-Wall -Werror -Wextra -g3
LIBS :=		-Llibft -lft
DANGER := -fsanitize=address
# READLINE = -L/Users/${USER}/.brew/opt/readline/lib -lreadline -L/goinfre/$(USER)/.brew/opt/readline/lib -lreadline
# READLINE2 = -I/${USER}/.brew/opt/readline/include -I/goinfre/$(USER)/.brew/opt/readline/include
READLINE = -lreadline -L ${HOME}/.brew/opt/readline/lib
READLINE2 = -I ${HOME}/.brew/opt/readline/include

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
	$(CC) $(CFLAGS) -c -o $@ $< $(READLINE2)
	@echo "\033[1A\033[0J\033[32;1m\rMinishell compilation >>\033[0m\033[30;1m $@\033[0m"

$(NAME) : $(OBJS)
	$(CC) -o $(NAME) $(OBJS) $(LIBS) $(READLINE)
clean :
	@make clean -sC libft
	$(RM) $(OBJS_DIR)

fclean : clean
	@make fclean -sC libft
	$(RM) $(NAME)

re : fclean all
