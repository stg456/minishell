/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: misimon <misimon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/12 17:25:37 by stgerard          #+#    #+#             */
/*   Updated: 2023/02/13 21:14:00 by misimon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	del(int j, t_minishell *shell)
{
	char	**newenv;
	int		i;
	int		h;

	h = 0;
	i = 0;
	while (shell->env[i] != NULL)
		i++;
	newenv = malloc(sizeof(char *) * i);
	i = 0;
	while (shell->env[i] != NULL)
	{
		if (i != j)
		{
			newenv[h] = shell->env[i];
			h++;
			i++;
		}
		else
			i++;
	}
	newenv[h] = NULL;
	shell->env = newenv;
}

void	ft_unset(t_node *actual_cmd, t_minishell *shell)
{
	int	i;
	int	j;

	j = 1;
	if (actual_cmd->cmd[0] && !actual_cmd->cmd[1])
		printf("unset: not enough arguments");
	while (actual_cmd->cmd[j] != NULL)
	{
		i = 0;
		while (shell->env[i] != NULL)
		{
			if (strcmp(actual_cmd->cmd[j], recupvar(shell->env[i])) == 0)
			{
				del(i, shell);
				break ;
			}
			else
				i++;
		}
		j++;
	}
}
