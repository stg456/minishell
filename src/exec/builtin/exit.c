/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: misimon <misimon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 17:41:49 by misimon           #+#    #+#             */
/*   Updated: 2023/03/13 18:13:25 by misimon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

void	exitnb(t_node *lst, t_minishell *shell)
{
	size_t	i;

	i = 0;
	while (lst->cmd[1][i])
	{
		if (ft_isalpha(lst->cmd[1][i]) == TRUE)
		{
			printf("exit\nMinishell: exit: %s: numeric argument required\n",
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
		printf("exit\nMinishell: exit: too many arguments\n");
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
