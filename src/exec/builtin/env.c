/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: misimon <misimon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 17:36:56 by misimon           #+#    #+#             */
/*   Updated: 2023/03/14 18:46:07 by misimon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

int	ft_env(t_node *lst, t_minishell *shell)
{
	size_t	i;

	i = -1;
	if (lst->cmd && lst->cmd[0] && !lst->cmd[1])
	{
		while (shell->env[++i])
			printf("%s\n", shell->env[i]);
		shell->status = 0;
	}
	else if (lst->cmd && lst->cmd[0] && lst->cmd[1])
	{
		printf("env: %s: No such file or directory\n", lst->cmd[1]);
		shell->status = 127;
	}
	return (shell->status);
}

// int	ft_env(t_minishell *shell)
// {
// 	size_t	i;

// 	i = -1;
// 	while (shell->env[++i])
// 		printf("%s\n", shell->env[i]);
// 	shell->status = 0;
// 	return (EXIT_SUCCESS);
// }