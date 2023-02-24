/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stgerard <stgerard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/12 17:25:37 by stgerard          #+#    #+#             */
/*   Updated: 2023/02/24 12:15:06 by stgerard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

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
			newenv[h++] = shell->env[i++];
		else
			i++;
	}
	newenv[h] = NULL;
	shell->env = newenv;
	shell->status = 0;
}

void	ft_unset(t_node *actual_cmd, t_minishell *shell)
{
	int	i;
	int	j;

	j = 1;
	if (actual_cmd->cmd[0] && ft_isdigit(actual_cmd->cmd[1][0]) == 1)
	{
		printf("bash: unset: `%s': not a valid identifier\n",
			actual_cmd->cmd[1]);
		shell->status = 1;
	}
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
