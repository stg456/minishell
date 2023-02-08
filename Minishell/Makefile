# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: misimon <misimon@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/12/08 19:06:31 by stgerard          #+#    #+#              #
#    Updated: 2023/02/08 19:29:35 by misimon          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

 #	NAME :
NAME	:= 	minishell
#	FILE :
SRC_DIR	:= 	src

SRCS	:=	builtins.c				\
			export.c				\
			minishell.c				\
			parse.c					\
			quote.c					\
			signal.c				\
			utils.c					\
			linked_list.c			\
			other_cmd.c				\


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