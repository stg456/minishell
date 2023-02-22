# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: misimon <misimon@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/10/19 00:55:09 by misimon           #+#    #+#              #
#    Updated: 2023/01/29 16:07:24 by misimon          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#	NAME :
NAME	:= 	libft.a

#	FILE :
SRC_DIR	:= 	src

SRCS	:=	is_fct/ft_isalpha.c			\
			is_fct/ft_isdigit.c			\
			is_fct/ft_isprint.c			\
			is_fct/ft_isascii.c			\
			is_fct/ft_isalnum.c			\
			is_fct/ft_issign.c			\
			is_fct/ft_isspace.c			\
										\
			ft_printf/ft_printf_hex.c	\
			ft_printf/ft_printf_other.c	\
			ft_printf/ft_printf_ptr.c	\
			ft_printf/ft_printf_uint.c	\
			ft_printf/ft_printf.c		\
										\
			ft_str_fct/ft_strjoin.c		\
			ft_str_fct/ft_strfjoin.c	\
			ft_str_fct/ft_strchr.c		\
			ft_str_fct/ft_strdup.c		\
			ft_str_fct/ft_strlcat.c		\
			ft_str_fct/ft_strlcpy.c		\
			ft_str_fct/ft_strlen.c		\
			ft_str_fct/ft_strrchr.c		\
			ft_str_fct/ft_strncmp.c		\
			ft_str_fct/ft_strnstr.c		\
			ft_str_fct/ft_substr.c		\
			ft_str_fct/ft_strtrim.c		\
			ft_str_fct/ft_strmapi.c		\
			ft_str_fct/ft_striteri.c	\
			ft_str_fct/ft_strcmp.c		\
										\
			getnextline/get_next_line.c	\
										\
			ft_put_fct/ft_putchar_fd.c	\
			ft_put_fct/ft_putstr_fd.c	\
			ft_put_fct/ft_putnbr_fd.c	\
			ft_put_fct/ft_putendl_fd.c	\
										\
			ft_convert_fct/ft_atoi.c	\
			ft_convert_fct/ft_bzero.c	\
			ft_convert_fct/ft_itoa.c	\
			ft_convert_fct/ft_split.c	\
			ft_convert_fct/ft_tolower.c	\
			ft_convert_fct/ft_toupper.c	\
										\
			ft_mem_fct/ft_memmove.c		\
			ft_mem_fct/ft_memcpy.c		\
			ft_mem_fct/ft_memset.c		\
			ft_mem_fct/ft_memcmp.c		\
			ft_mem_fct/ft_memccpy.c		\
			ft_mem_fct/ft_memchr.c		\
			ft_mem_fct/ft_calloc.c		\
										\
			ft_end_fct/ft_error.c		\
										\
			ft_free_fct/ft_tabfree.c	\

SRCS := 	$(SRCS:%=$(SRC_DIR)/%)

#	COMPILATION:
CC := 		@gcc
CFLAGS := 	-Wall -Werror -Wextra

#	STATIC LIB CREATION:
AR :=		@ar
ARFLAG :=	-rcs

#	BUILD:
OBJS_DIR := .build
OBJS = $(SRCS:$(SRC_DIR)/%.c=$(OBJS_DIR)/%.o)

#	TOOLS:

RM	:= @rm -rf
DUP_DIR = @mkdir -p $(@D)
CREATE_DIR = [ ! -d $(OBJS_DIR) ] && mkdir $(OBJS_DIR)
ALLOBJS = $(OBJS_DIR)/%.o

#	COMMAND:

all : $(NAME)

.create.build :
	$(CREATE_DIR)

$(NAME) : $(OBJS)
	$(AR) $(ARFLAG) $(NAME) $(OBJS)
	@echo "\033[1A\033[0J\033[32;1m\r$(NAME) created !\033[0m"

$(OBJS_DIR)/%.o : $(SRC_DIR)/%.c
	$(DUP_DIR)
	$(CC) $(CFLAGS) -c -o $@ $<
	@echo "\033[1A\033[0J\033[32;1m\rLibft compilation >>\033[0m\033[30;1m $@\033[0m"

clean : 
	$(RM) $(OBJS_DIR)

fclean : clean
	$(RM) $(NAME)

re : fclean all
