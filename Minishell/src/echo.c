/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stgerard <stgerard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 10:52:18 by stgerard          #+#    #+#             */
/*   Updated: 2023/02/13 12:12:32 by stgerard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	ft_echo(t_node *lst, t_node *actual_cmd, t_minishell *shell)
{
	(void) actual_cmd;
	(void) shell;
	size_t	i;
	// char	*var;
	// char	*val;

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
	printf("%s\n", lst->cmd[1]);
	printf("%c\n", lst->cmd[1][0]);
	if (lst->cmd[1][0] == '$' && lst->cmd) // seg fault si $
	{
		printf("%c\n", lst->cmd[1][0]);
	}
	return (EXIT_SUCCESS);
}

// pas bon , $ et $?