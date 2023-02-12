/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stgerard <stgerard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 16:07:27 by stgerard          #+#    #+#             */
/*   Updated: 2023/02/12 12:48:25 by stgerard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int			detect(char *actual_cmd, t_minishell *shell)
{
	size_t	i;
	size_t	j;
	char	*newvar;

	i = 0;
	j = 0;
	while (actual_cmd[1] != '=')
		i++;
	newvar = malloc(sizeof(char *) * i + 1);
	while (j < i)
		newvar[j++] = actual_cmd[j++];
	printf("%s\n", newvar);
	i = 0;
	j = 0;
	while (shell->env[j] != NULL)
	{
		while ()
		if (newvar == shell->env[j])

		new var 
		if ()
		j++;
	}
}

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
		newenv[j] = ft_strdup(shell->env[j]);
		j++;
	}
	newenv[j] = ft_strdup(actual_cmd);
	newenv[j + 1] = NULL;
	shell->env = newenv;
} // free

int	ft_export(t_node *actual_cmd, t_minishell *shell)
{
	if (actual_cmd->cmd && !actual_cmd->cmd[1])
		ft_env(shell);
	else if (actual_cmd && detect(actual_cmd->cmd[1], shell) == 1)
		{
			printf("detected !\n");
			// unset puis set
		}
	else
		addvar(actual_cmd->cmd[1], shell);
	return 0;
} // pas encore, un tout petit debut de fct

// int	ft_unset(char *actual_cmd, t_minishell *shell)
//  {
	
//  }