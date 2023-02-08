/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stgerard <stgerard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 16:07:27 by stgerard          #+#    #+#             */
/*   Updated: 2023/02/08 18:30:36 by stgerard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	ft_export(t_node *actual_cmd, t_minishell *shell)
{
	int		i;
	
	i = 0;
	if (actual_cmd && !actual_cmd->next)
		ft_env(shell);
	else if (actual_cmd->token && actual_cmd->next)
		actual_cmd = actual_cmd->next;

	if (actual_cmd->token)
	{
		printf("variable avec valeur: %s\n", actual_cmd->token);
		i = 0;
		// while (actual_cmd->token[i++])
		// {
		// 	if (actual_cmd->token[i++] != '=')
		// 		break ;
		// 	actual_cmd->var[i] = actual_cmd->token[i];
		// }
	

		actual_cmd->varvalue = ft_split(actual_cmd->token, '=');
		i = 0;

		printf("varvalue[0]: %s\n", actual_cmd->varvalue[0]);
		printf("varvalue[1]: %s\n", actual_cmd->varvalue[1]);

		// verif si existe
		// getenv(); varvalue[0] ????

		// change si existe
		// if (varvalue[0]) change varvalue[1] ????

		// mettre dams env

		while (shell->env[i]) // seg fault
			i++;
		printf("a");
		i = 0;
		while (actual_cmd->varvalue[0])
		{
			shell->env[i] = actual_cmd->varvalue[0];
			i++;
		}
		printf("a");
		// actual_cmd->next->token = actual_cmd->token;
		// printf("%s\n", actual_cmd->token);
		// ne marche pas et seg fault !!!

	}
	return 0;
}

// pas encore, un tout petit debut de fct