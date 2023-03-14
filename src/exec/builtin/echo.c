/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: misimon <misimon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 10:52:18 by stgerard          #+#    #+#             */
/*   Updated: 2023/03/06 13:43:26 by misimon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

void	affecho(t_node *lst, size_t	i)
{
	while (lst->cmd[++i])
	{
		printf("%s", lst->cmd[i]);
		if (lst->cmd[i + 1])
			printf(" ");
	}
}

int	ft_echo(t_node *lst, t_minishell *shell)
{
	size_t	i;

	i = 0;
	if (lst->cmd && lst->cmd[0] && !lst->cmd[1])
		return (write(1, "\n", 1));
	if (lst->cmd && lst->cmd[1] && ft_strcmp(lst->cmd[1], "-n") != 0)
	{
		affecho(lst, i);
		printf("\n");
	}
	else if (lst->cmd && lst->cmd[i] && ft_strcmp(lst->cmd[1], "-n") == 0)
		affecho(lst, ++i);
	shell->status = 0;
	return (shell->status);
}
