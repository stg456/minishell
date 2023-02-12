/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stgerard <stgerard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 16:46:01 by stgerard          #+#    #+#             */
/*   Updated: 2023/02/12 17:49:50 by stgerard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	ft_exit(t_node *lst)
{
	if (lst->cmd[0] && !lst->cmd[1])
	{
		exit(EXIT_SUCCESS);
	}
	else
		printf("exit: too many arguments\n");
}

int	ft_env(t_minishell *shell)
{
	size_t	i;
	int		j;

	j = 0;
	i = -1;
	while (shell->env[++i])
		printf("%s\n", shell->env[i]);
	return (EXIT_SUCCESS);	
}

int	ft_pwd(t_node *lst)
{
	char	buffer[256];

	if (lst->cmd && lst->cmd[0] && !lst->cmd[1])
	{
		if (getcwd(buffer, 256) == NULL)
		{
			perror("Cannot get current working directory path\n");
			if (errno == ERANGE)
				perror("Buffer size is too small.\n");
			exit(EXIT_FAILURE);
    	}
		printf("%s\n", buffer);
	}
	else if (lst->cmd && lst->cmd[1])
		printf("pwd: too many arguments\n");
	return EXIT_SUCCESS;
}

int		ft_echo(t_node *lst)
{
	size_t i;

	i = 0;
	if (lst->cmd && lst->cmd[i] && !lst->cmd[i + 1])
		return (write(1, "\n", 1));
	if (lst->cmd && lst->cmd[++i] && ft_strcmp(lst->cmd[i], "-n") != 0)
	{
		while (lst->cmd[i])
		{
			lst->cmd[i] = ft_strtok(lst->cmd[i], "\"", 7);
			printf("%s", lst->cmd[i]);
			if (lst->cmd[i + 1] && lst->cmd[i])
				printf(" ");
			i++;
		}
		printf("\n");
	}
	else if (lst->cmd && lst->cmd[i] && ft_strcmp(lst->cmd[i], "-n") == 0)
	{
		while (lst->cmd[++i])
		{
			lst->cmd[i] = ft_strtok(lst->cmd[i], "\"", 7);
			printf("%s", lst->cmd[i]);
			if (lst->cmd[i + 1] && lst->cmd[i])
				printf(" ");
		}
	}
	return EXIT_SUCCESS;
}

int	ft_cd(t_minishell *shell, t_node *lst)
{
	size_t		i;
	size_t		j;

	j = 0;
	shell->dir = getenv("PWD=");
	if (lst->cmd && lst->cmd[j] && !lst->cmd[j + 1])
	{
		shell->dir = getenv("HOME=");
		chdir(shell->dir);
	}
	else if (lst->cmd && lst->cmd[j] && lst->cmd[++j] && !lst->cmd[j + 1])
	{
		i = chdir(lst->cmd[j]);
		chdir(lst->token);
	}
	return 0;
}

// manque le ~ pour cd
// manque le $ pour echo
// manque le ='' pour export
// manque le heredoc
// manque le cas des quotes non fermes pour echo
