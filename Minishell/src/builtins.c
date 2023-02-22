/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stgerard <stgerard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 16:46:01 by stgerard          #+#    #+#             */
/*   Updated: 2023/02/22 17:24:46 by stgerard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	exitnb(t_node *lst, t_minishell *shell)
{
	size_t	i;

	i = 0;
	while (lst->cmd[1][i])
	{
		if (ft_isalpha(lst->cmd[1][i]) == TRUE)
		{
			printf("exit\nbash: exit: %s: numeric argument required\n",
				lst->cmd[1]);
			shell->status = 255;
			break ;
		}
		else
		{
			shell->status = ft_atoi(lst->cmd[1]);
			printf("%d\n", shell->status);
		}
		i++;
	}
	exit(shell->status);
}

void	ft_exit(t_node *lst, t_minishell *shell)
{
	if (lst->cmd[0] && lst->cmd[1] && lst->cmd[2])
	{
		printf("exit\nbash: exit: too many arguments\n");
		shell->status = 1;
	}
	else if (lst->cmd[0] && lst->cmd[1] && !lst->cmd[2])
		exitnb(lst, shell);
	else if (lst->cmd[0] && !lst->cmd[1])
	{
		shell->status = 0;
		exit(EXIT_SUCCESS);
	}
	exit(shell->status);
}

int	ft_env(t_minishell *shell)
{
	size_t	i;
	int		j;

	j = 0;
	i = -1;
	while (shell->env[++i])
		printf("%s\n", shell->env[i]);
	shell->status = 0;
	return (EXIT_SUCCESS);
}

int	ft_pwd(t_node *lst, t_minishell *shell)
{
	char	buffer[256];

	if (lst->cmd && lst->cmd[0])
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
	shell->status = 0;
	return (EXIT_SUCCESS);
}

// exit parait bon
// pour echo le $? pas parfait, ne s'actualise pas !
// affichage d'une variable dans env ou export pas conforme !!!
// le heredoc
// manque le cas des quotes non fermes pour echo
// odre alpha pour env

// bash: dfijeroigeior: command not found, seg fault