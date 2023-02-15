/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: misimon <misimon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/11 14:47:42 by stgerard          #+#    #+#             */
/*   Updated: 2023/02/15 17:20:21 by misimon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	ft_free_shell(t_minishell *shell)
{
	close(shell->fd_in);
	close(shell->fd_out);

	// free les cellules du tableau
	// /!\ free le tableau

	free(shell->path);
	free(shell->env);
	free(shell);
	// free les cellules des tableaux
	// /!\ free les doubles tableaux
}

t_minishell	*ft_init(void)
{
	t_minishell	*shell;
	int			i;
	extern char	**environ;

	i = 0;
	shell = malloc(sizeof(t_minishell));
	shell->cmd = create_list();
	if (!shell || !shell->cmd)
		return (NULL);
	while (environ[i])
		i++;
	shell->env = (char **)malloc(sizeof(char *) * i + 1);
	i = -1;
	while (environ[++i])
		shell->env[i] = ft_strdup(environ[i]);
	shell->path = ft_split(getenv("PATH"), ':');
	shell->fd_in = 0;
	shell->fd_out = 0;
	return (shell);
}

int	check_input(char *str)
{
	size_t	i;

	i = 0;
	if (!str)
		return (-1);
	if (str[0] == '\0')
		return (0);
	while (str[i])
	{
		if (ft_isascii(str[i]) == 1 && ft_isspace(str[i]) == 0)
			return (1);
		++i;
	}
	return (0);
}

void	do_cmd(t_minishell *shell, char *buf)
{
	if (check_input(buf) == 1)
		add_history(buf);
	other_cmd(shell);
}

void	ft_prompt(void)
{
	char			*buf;
	t_minishell		*shell;

	buf = NULL;
	shell = ft_init();
	while (1)
	{
		if (buf)
			free(buf);
		buf = readline("Minishell$> ");
		if (!buf)
			exit(EXIT_SUCCESS);
		if (ft_in_quote(buf) == 1)
		{
			cmd_parsing(buf, shell);
			do_cmd(shell, buf);
			delete_all_list(shell->cmd);
		}
		else
			printf("Bad number of quote\n");
		// free(buf);
		// builtins(buf);

	}
	// ft_free_shell(shell);
}

int	main(int ac, char **av)
{
	(void)ac;
	(void)av;
	// t_minishell		*shell;

	signal(SIGINT, sigint_handler);
	signal(SIGQUIT, sigint_handler);

	ft_prompt();
	
	// ft_free_shell(shell);
}
