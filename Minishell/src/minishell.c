/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stgerard <stgerard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/11 14:47:42 by stgerard          #+#    #+#             */
/*   Updated: 2023/02/07 16:38:01 by stgerard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	ft_free_shell(t_minishell *shell)
{
	close(shell->fd_in);
	close(shell->fd_out);
	// /!\ free un tableau

	free(shell->path);
	free(shell->env);
	free(shell);
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
	shell->env[i] = 0;
	i = 0;
	while (environ[i])
	{
		shell->env[i] = ft_strdup(environ[i]);
		i++;
	}
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
	t_node	*actual_cmd;
	t_node	*lst;
	// t_set	*inenv;

	lst = NULL;
	actual_cmd = shell->cmd->head;
	while (actual_cmd != NULL)
	{
		if (check_input(buf) == 1)
			add_history(buf);
		if (!actual_cmd->prev || actual_cmd->prev->is_cmd == FALSE)
		{
			if (ft_strcmp(actual_cmd->token, "env") == 0)
				ft_env(shell);
			else if (ft_strcmp(actual_cmd->token, "pwd") == 0)
				ft_pwd(actual_cmd);
			else if (ft_strcmp(actual_cmd->token, "echo") == 0)
				ft_echo(actual_cmd);
			else if (ft_strcmp(actual_cmd->token, "export") == 0)
				ft_export(actual_cmd, shell);
			else if (ft_strcmp(actual_cmd->token, "cd") == 0)
				ft_cd(shell, actual_cmd);
			// else if (ft_strcmp(actual_cmd->token, "exit"))
			// 	exit (0);
			else
				printf("stop\n");
		}
		actual_cmd = actual_cmd->next;
	}
}

void	ft_prompt(void)
{
	char			*buf;
	t_minishell		*shell;

	signal(SIGINT, sigint_handler);
	signal(SIGQUIT, sigint_handler);

	buf = NULL;
	shell = ft_init();
	while (1)
	{
		if (buf)
			free(buf);
		buf = readline("Minishell$> ");
		cmd_parsing(buf, shell);
		do_cmd(shell, buf);
		delete_all_list(shell->cmd);
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

	ft_prompt();
	
	// ft_free_shell(shell);
}
