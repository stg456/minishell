/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: misimon <misimon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 19:08:23 by stgerard          #+#    #+#             */
/*   Updated: 2023/03/14 19:21:27 by misimon          ###   ########.fr       */
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

enum e_node_type
{
	UNDEFINED = -1,
	PIPE = 0,
	CMD,
	OUTPUT_DIR,
	INPUT_DIR,
	QUOTE,
	DQUOTE,
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
	int		new_fd[2];
	int		old_fd[2];
}				t_minishell;

// main.c

// prompt_init.c

t_minishell	*sh_init(char **envp);

// parse.c

void		delete_next(t_list *lst, t_node *node);
char		*ft_strtok(char *str, char *delimiter, char replace);
char		*cmd_path(t_minishell *shell);
void		cmd_parsing(char *buf, t_minishell *shell);
char		*do_var_replacement(char *str, t_minishell *ms);
size_t		var_len_start(char *str);
size_t		name_len(char *str);
char		*ft_strndup(char *s1, size_t n, size_t start);
void		open_fd(t_minishell *ms);
void		check_token_var(t_node *node, t_minishell *ms);
t_bool		which_type(char *str, t_node *cmd);
void		which_cmd_fork(t_node *cmd, t_minishell *ms);
t_bool		which_cmd_no_fork(t_node *cmd, t_minishell *ms);
void		set_default_fd(t_minishell *ms);
t_bool		check_exist(t_minishell *ms);

// linked_list.c

t_list		*create_list(void);
void		delete_all_list(t_list *ptr);
void		add_tail(t_list *ptr, char *cmd);
t_list		*delete_position(t_list *ptr, size_t position);

// other_cmd.c

size_t		count_pipe(t_list *list);
void		other_cmd(t_minishell *shell);

// builtins.c

void		ft_exit(t_node *lst, t_minishell *shell);
int			ft_env(t_node *lst, t_minishell *shell);
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

void		affecho(t_node *lst, size_t	i);
int			ft_echo(t_node *lst, t_minishell *shell);

// cd.c

void		abst(t_minishell *shell, t_node *lst);
void		direct(t_minishell *shell, t_node *lst);
void		home(t_minishell *shell, t_node *lst);
int			ft_cd(t_minishell *shell, t_node *lst);

// quote.c

t_bool		check_quote(char *buf);
char		*replace_quote_space(char *buf);
t_bool		ft_in_quote(char **buf);

// signal.c

void		sigint_handler(int signum);

#endif