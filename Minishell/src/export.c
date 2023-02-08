/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stgerard <stgerard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 16:07:27 by stgerard          #+#    #+#             */
/*   Updated: 2023/02/08 20:12:07 by stgerard         ###   ########.fr       */
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
		
	// ft_env(shell);

	// return 0;
}

int	ft_export(t_node *actual_cmd, t_minishell *shell)
{
	// size_t		i;
	// size_t		j;
	// char		**newenv;
	
	// i = 0;
	// j = 0;
	if (actual_cmd && !actual_cmd->next)
		ft_env(shell);
	else if (actual_cmd->token && actual_cmd->next)
		actual_cmd = actual_cmd->next;

	addvar(actual_cmd->token, shell);


// 	if (actual_cmd->token)
// 	{
// 		printf("variable avec valeur: %s\n", actual_cmd->token);
// 		i = 0;

// 	// actual_cmd->varvalue = ft_split(actual_cmd->token, '=');
// 	// 	printf("varvalue[0]: %s\n", actual_cmd->varvalue[0]);
// 	// 	printf("varvalue[1]: %s\n", actual_cmd->varvalue[1]);

// 		char	**newenv;

// 		while (shell->env[i] != NULL)
// 			i++;
		
// 		newenv = malloc(sizeof(char *) * i + 2);
// 		while (j < i)
// 		{
// 			newenv[j] = shell->env[j];
// 			j++;
// 		}
// 		newenv[j] = ft_strdup(actual_cmd->token);
// 		newenv[j + 1] = NULL;
// 		shell->env = newenv;
		
// 		ft_env(shell);
// 	}
	return 0;
}

// pas encore, un tout petit debut de fct