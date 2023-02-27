/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: misimon <misimon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 10:52:18 by stgerard          #+#    #+#             */
/*   Updated: 2023/02/27 15:32:51 by misimon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

void	prtval(char	*value, t_minishell *shell)
{
	size_t	i;

	i = 0;
	while (value[i] != '=')
		i++;
	i++;
	while (value[i] != '\0')
	{
		write(1, &value[i], 1);
		i++;
	}
	shell->status = 0;
	write(1, " ", 1);
}

void	prtvar(char *param, t_minishell *shell)
{
	size_t	i;
	size_t	j;
	char	*nvar;

	i = 0;
	j = 0;
	while (shell->env[j])
	{
		nvar = recupvar(shell->env[j]);
		if (strcmp(nvar, param) == 0)
			prtval(shell->env[j], shell);
		j++;
	}
}

char	*vardol(char *param, t_minishell *shell)
{
	char	*var;
	size_t	j;
	size_t	i;

	i = 0;
	j = 1;
	var = malloc(sizeof(char *) * ft_strlen(param));
	while (param[j])
	{
		var[i] = param[j];
		i++;
		j++;
	}
	var[i] = '\0';
	shell->status = 0;
	return (var);
}

void	affecho(t_node *lst, size_t	i, t_minishell *shell)
{
	char	*var;

	while (lst->cmd[++i])
	{
		if (lst->cmd[i][0] == '$' && lst->cmd[i][1] == '?')
		{
			wait(&shell->status);
			printf("%d\n", shell->status);
			shell->status = 0;
		}
		else if (lst->cmd[i][0] == '$')
		{
			var = vardol(lst->cmd[i], shell);
			prtvar(var, shell);
			shell->status = 0;
		}
		else
		{
			lst->cmd[i] = ft_strtok(lst->cmd[i], "\"", 7);
			printf("%s", lst->cmd[i]);
		}
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
		affecho(lst, i, shell);
		printf("\n");
	}
	else if (lst->cmd && lst->cmd[i] && ft_strcmp(lst->cmd[1], "-n") == 0)
		affecho(lst, ++i, shell);
	shell->status = 0;
	return (shell->status);
}
