/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stgerard <stgerard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 16:46:01 by stgerard          #+#    #+#             */
/*   Updated: 2023/02/17 15:52:40 by stgerard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	ft_exit(t_node *lst)
{
	if (lst->cmd[0] && !lst->cmd[1])
	{
		// shell->status = 0;
		exit(EXIT_SUCCESS);
	}
	else
		printf("exit: too many arguments\n");
}

// bash: exit: abc: numeric argument required

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
	shell->status = 0;
	return (EXIT_SUCCESS);
}

// cd ~/minishell ne narche pas !!!

// pour echo manque le $?
// pour export manque le =''
// manque le heredoc
// manque le cas des quotes non fermes pour echo
// odre alpha pour env