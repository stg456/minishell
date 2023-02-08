/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stgerard <stgerard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 16:07:27 by stgerard          #+#    #+#             */
/*   Updated: 2023/02/08 20:16:44 by stgerard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void		addvar(char *actual_cmd, t_minishell *shell)
{
	size_t		i;
	size_t		j;
	char		**newenv;

	i = 0;
	j = 0;

	while (shell->env[i] != NULL)
			i++;	
	newenv = malloc(sizeof(char *) * i + 2);
	while (j < i)
	{
		newenv[j] = shell->env[j];
		j++;
	}
	newenv[j] = ft_strdup(actual_cmd);
	newenv[j + 1] = NULL;
	shell->env = newenv;
}

int	ft_export(t_node *actual_cmd, t_minishell *shell)
{
	if (actual_cmd && !actual_cmd->next)
		ft_env(shell);
	else if (actual_cmd->token && actual_cmd->next)
		actual_cmd = actual_cmd->next;

	addvar(actual_cmd->token, shell);

	return 0;
}

// pas encore, un tout petit debut de fct