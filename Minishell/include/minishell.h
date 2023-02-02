/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stgerard <stgerard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 19:08:23 by stgerard          #+#    #+#             */
/*   Updated: 2023/02/02 14:15:02 by stgerard         ###   ########.fr       */
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

typedef struct s_node
{
	char			**cmd;
	char			*path;
	struct s_node	*next;
	struct s_node	*prev;
}	t_node;

typedef struct s_list
{
	size_t	size;
	t_node	*head;
	t_node	*tail;
}	t_list;

/*
	Ajout de la structure pour les Linked list (n'hésite pas à me demander si ta des questions sur ma partie) mais sache que
	le faire de cette manière est quasiment obligatoire pour faciliter le parsing ne serais ce que pour reconstituer correctement
	la commande.
*/

typedef struct s_minishell
{
	t_list	*cmd;
	char	**env;
	char	**path;
	char	*dir;
	int		fd_in;
	int		fd_out;
}				t_minishell;

// minishell.c

int			main(int ac, char **av);
void		ft_prompt(void);
t_minishell	*ft_init(void);
void		ft_free_shell(t_minishell *shell);

// parse.c

char		*ft_strtok(char *str, char *delimiter);
char		*cmd_path(t_minishell *shell);
void		cmd_parsing(char *buf, t_minishell *shell);

// linked_list.c

t_list		*create_list(void);
void		delete_all_list(t_list *ptr);
void		add_tail(t_list *ptr, char **cmd);

// builtins.c

void		ft_exit(t_node *lst);
int			ft_env(t_minishell *shell);
int			ft_pwd(t_node *lst);
int			ft_echo(t_node *lst);
int			ft_export(t_node *lst);
int			ft_cd(t_minishell *shell, t_node *lst);

// quote.c

int			ft_in_quote(char *c, int i);

// signal.c

void		sigint_handler(int sig_num);

// utils

char		*trimer(char *s1, char *buf);

#endif