/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stgerard <stgerard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 16:46:01 by stgerard          #+#    #+#             */
/*   Updated: 2023/02/21 15:32:35 by stgerard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	ft_exit(t_node *lst, t_minishell *shell)
{
	size_t	i;

	i = 0;
	if (lst->cmd[0] && !lst->cmd[1])
	{
		shell->status = 0;
		exit(EXIT_SUCCESS);
	}
	else if (lst->cmd[0] && lst->cmd[1])
	{
		if (lst->cmd[1] && (ft_isalpha(lst->cmd[1][i]) == TRUE))
			i++;
		else
		{
			shell->status = 0;
			exit(EXIT_SUCCESS);
		}
	}
	shell->status = 255;
	printf("exit\nbash: exit: abc: numeric argument required\n");
	exit(EXIT_FAILURE);
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

// pour echo le $? pas parfait, ne s'actualise pas !
// pour export manque le =''
// manque le heredoc
// manque le cas des quotes non fermes pour echo
// odre alpha pour env
