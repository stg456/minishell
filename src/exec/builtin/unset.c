/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: misimon <misimon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/12 17:25:37 by stgerard          #+#    #+#             */
/*   Updated: 2023/03/14 18:29:27 by misimon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

size_t	tab_len(char **tab)
{
	size_t	i;

	i = 0;
	while (tab[i])
		i++;
	return (i);
}

void	del(int j, t_minishell *ms)
{
	char	**new;
	int		i;

	new = malloc(sizeof(char *) * tab_len(ms->env));
	i = 0;
	while (i < j)
	{
		new[i] = ft_strdup(ms->env[i]);
		i++;
	}
	j++;
	while (ms->env[j])
	{
		new[i] = ft_strdup(ms->env[j]);
		i++;
		j++;
	}
	free_tab(ms->env);
	ms->env = new;
}

void	ft_unset(t_node *actual_cmd, t_minishell *shell)
{
	int	i;
	int	j;

	j = 1;
	if (actual_cmd->cmd[0] && ft_isdigit(actual_cmd->cmd[1][0]) == 1)
	{
		printf("Minishell: unset: `%s': not a valid identifier\n",
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

// void	del(int j, t_minishell *shell)
// {
// 	char	**newenv;
// 	int		i;
// 	int		h;

// 	h = 0;
// 	i = 0;
// 	while (shell->env[i] != NULL)
// 		i++;
// 	newenv = malloc(sizeof(char *) * i);
// 	if (!newenv)
// 		exit(1);
// 	i = 0;
// 	while (shell->env[i] != NULL)
// 	{
// 		if (i != j)
// 		{
// 			newenv[h] = shell->env[i++];
// 			printf("%s\n", newenv[h]);
// 			h++;
// 		}
// 		else
// 			i++;
// 	}
// 	newenv[h] = NULL;
// 	shell->env = newenv;
// 	shell->status = 0;
// }