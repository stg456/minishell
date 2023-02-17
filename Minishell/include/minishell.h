/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stgerard <stgerard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 19:08:23 by stgerard          #+#    #+#             */
/*   Updated: 2023/02/17 15:52:40 by stgerard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <string.h>
# include <errno.h>
# include <sys/wait.h>
# include <termios.h>
# include <curses.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <stdint.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <signal.h>
# include "../libft/libft.h"
# include "readline/history.h"
# include "readline/readline.h"

enum node_type
{
	UNDEFINED = -1,
	PIPE = 0,
	CMD,
	OUTPUT_DIR,
	INPUT_DIR,
};

typedef struct s_node
{
	char			*token;
	char			**cmd;
	char			*path;
	int				fd[2];
	t_bool			type;
	struct s_node	*next;
	struct s_node	*prev;
}	t_node;

typedef struct s_list
{
	size_t	size;
	size_t	nbr_cmd;
	size_t	nbr_pipe;
	char	**all_path;
	t_node	*head;
	t_node	*tail;
}				t_list;

typedef struct s_minishell
{
	t_list	*cmd;
	char	**env;
	char	**path;
	char	*dir;
	int		status;
	int		fd_in;
	int		fd_out;
}				t_minishell;

// minishell.c

void		ft_prompt(void);
t_minishell	*ft_init(void);
void		ft_free_shell(t_minishell *shell);

// parse.c

char		*ft_strtok(char *str, char *delimiter, char replace);
char		*cmd_path(t_minishell *shell);
void		cmd_parsing(char *buf, t_minishell *shell);

// linked_list.c

t_list		*create_list(void);
void		delete_all_list(t_list *ptr);
void		add_tail(t_list *ptr, char *cmd);
t_list		*delete_position(t_list *ptr, size_t position);

// other_cmd.c

size_t		count_pipe(t_list *list);
void		other_cmd(t_minishell *shell);

// builtins.c

void		ft_exit(t_node *lst);
int			ft_env(t_minishell *shell);
int			ft_pwd(t_node *lst, t_minishell *shell);

// export.c

int			ft_export(t_node *actual_cmd, t_minishell *shell);
void		addvar(char *actual_cmd, t_minishell *shell);
int			ft_export_unset(char *actual_cmd, t_minishell *shell);
int			detect(char *actual_cmd, t_minishell *shell);
char		*recupvar(char *actual_cmd);

// unset.c

void		del(int j, t_minishell *shell);
void		ft_unset(t_node *actual_cmd, t_minishell *shell);

// echo.c

void		prtval(char	*value, t_minishell *shell);
void		prtvar(char *param, t_minishell *shell);
char		*vardol(char *param, t_minishell *shell);
void		affecho(t_node *lst, size_t	i, t_minishell *shell);
int			ft_echo(t_node *lst, t_minishell *shell);

// cd.c

// char		*recupcmd(t_minishell *shell, t_node *lst);
void		home(t_minishell *shell, t_node *lst);
int			ft_cd(t_minishell *shell, t_node *lst);

// quote.c

int			ft_in_quote(char *c);

// signal.c

void		sigint_handler(int signum);

// utils

char		*trimer(char *s1, char *buf);

#endif