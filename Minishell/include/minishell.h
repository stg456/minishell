/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: misimon <misimon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 19:08:23 by stgerard          #+#    #+#             */
/*   Updated: 2023/01/26 16:32:59 by misimon          ###   ########.fr       */
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

typedef struct s_minishell
{
	// int		ac; //  temporairement pas besoin
	// char	**av; // temporairement pas besoin
	char	**env;
	char	**path;
	char	*cmd;
	int		fd_in;
	int		fd_out;
}				t_minishell;

// minishell.c

int			main(int ac, char **av);
void		ft_prompt(void);
t_minishell	*ft_init(void);
void		ft_free_shell(t_minishell *shell);

// parse.c

// void		ft_parse(char *buf, t_minishell *shell);

// builtins.c

// void		ft_exit(t_minishell *shell);
int			ft_env(t_minishell *shell);
int			ft_pwd(t_minishell *shell);
int			ft_echo(char *buf);

// quote.c

int			ft_in_quote(char *c, int i);

// signal.c

void		sigint_handler(int sig_num);

// utils

char		*trimecho(char *s1);

#endif