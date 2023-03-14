/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stgerard <stgerard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 16:07:27 by stgerard          #+#    #+#             */
/*   Updated: 2023/02/23 13:45:19 by stgerard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

char	*recupvar(char *actual_cmd)
{
	size_t	i;
	size_t	j;
	char	*newvar;

	i = 0;
	j = 0;
	while (actual_cmd[i] != '=' && actual_cmd[i] != '\0')
		i++;
	newvar = malloc(sizeof(char) * (i + 1));
	while (j < i)
	{
		newvar[j] = actual_cmd[j];
		j++;
	}
	newvar[j] = '\0';
	return (newvar);
}

int	detect(char *actual_cmd, t_minishell *shell)
{
	int		i;
	int		j;
	char	*varcmd;
	char	*varenv;

	i = 0;
	j = 0;
	varcmd = recupvar(actual_cmd);
	while (shell->env[j] != NULL)
	{
		varenv = recupvar(shell->env[j]);
		if (ft_strcmp(varcmd, varenv) == 0)
			return (j);
		else
			j++;
	}
	return (-1);
}

void	addvar(char *actual_cmd, t_minishell *shell)
{
	size_t		i;
	size_t		j;
	char		**newenv;

	i = 0;
	j = 0;
	while (shell->env[i] != NULL)
		i++;
	newenv = malloc(sizeof(char *) * (i + 2));
	while (shell->env[j] != NULL)
	{
		newenv[j] = ft_strdup(shell->env[j]);
		j++;
	}
	newenv[j] = ft_strdup(actual_cmd);
	newenv[j + 1] = NULL;
	shell->env = newenv;
}

int	ft_export(t_node *actual_cmd, t_minishell *shell)
{
	size_t	i;

	i = 0;
	if (actual_cmd->cmd && !actual_cmd->cmd[1])
		ft_env(actual_cmd, shell);
	else
	{
		while (actual_cmd->cmd[++i] != NULL)
		{
			if (actual_cmd && detect(actual_cmd->cmd[i], shell) >= 0)
			{
				ft_export_unset(actual_cmd->cmd[i], shell);
				addvar(actual_cmd->cmd[i], shell);
			}
			else
				addvar(actual_cmd->cmd[i], shell);
		}
	}
	return (0);
}

int	ft_export_unset(char *cmd, t_minishell *shell)
{
	int		i;
	int		j;
	char	**nextenv;
	int		ex;

	i = 0;
	j = 0;
	while (shell->env[i] != NULL)
			i++;
	nextenv = malloc(sizeof(char *) * i);
	ex = detect(cmd, shell);
	i = 0;
	while (shell->env[j] != NULL)
	{
		if (j != ex)
			nextenv[i++] = ft_strdup(shell->env[j++]);
		else
			j++;
	}
	nextenv[++i] = 0;
	shell->env = nextenv;
	return (0);
}
