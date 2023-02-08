/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: misimon <misimon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 19:08:23 by stgerard          #+#    #+#             */
/*   Updated: 2023/02/08 17:50:58 by misimon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <string.h>
# include <errno.h>
# include <sys/wait.h>
# include <termios.h>
# include <curses.h>
# include <stdint.h>
# include <sys/stat.h>
# include <signal.h>
# include "../libft/libft.h"
# include <readline/readline.h>
# include <readline/history.h>

// typedef struct	s_set
// {
// 	char	*var;
// 	char	*value;
// 	char	**varvalue;
// 	t_set	*next;
// 	t_bool	set;
// }				t_set;

typedef struct s_node
{
	char			*token;
	char			**cmd;
	char			*varvalue;
	char			*var;
	char			*value;
	char			*path;
	t_bool			is_cmd;
	struct s_node	*next;
	struct s_node	*prev;
}	t_node;

typedef struct s_list
{
	size_t	size;
	t_node	*head;
	t_node	*tail;
}				t_list;

typedef struct s_minishell
{
	t_list	*cmd;
	char	**env;
	char	**path;
	char	*dir;
	int		fd_in;
	int		fd_out;
	// t_set	*inenv;
}				t_minishell;

// minishell.c

int			main(int ac, char **av);
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
int			ft_pwd(t_node *lst);
int			ft_echo(t_node *lst);
int			ft_export(t_node *actual_cmd, t_minishell *shell);
int			ft_cd(t_minishell *shell, t_node *lst);

// quote.c

int			ft_in_quote(char *c, int i);

// signal.c

void		sigint_handler(int signum);

// utils

char		*trimer(char *s1, char *buf);

#endif