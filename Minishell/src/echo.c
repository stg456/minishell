/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stgerard <stgerard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 10:52:18 by stgerard          #+#    #+#             */
/*   Updated: 2023/02/14 17:52:36 by stgerard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	prtval(char	*value)
{
	int	i;

	i = 0;
	while (value[i] != '=')
		i++;
	i++;
	while (value[i] != '\0')
	{
		write(1, &value[i], 1);
		write(1, " ", 1);
		i++;
	}
	return ;
}

void	prtvar(char *param, t_minishell *shell)
{
	int		i;
	int		j;
	char	*nvar;

	i = 0;
	j = 0;
	while (shell->env[j])
	{
		nvar = recupvar(shell->env[j]);
		if (strcmp(nvar, param) == 0)
			prtval(shell->env[j]);
		j++;
	}
}

char	*vardol(char *param)
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
	return (var);
}

void	affecho(t_node *lst, size_t	i, t_minishell *shell)
{
	char	*var;

	while (lst->cmd[++i])
	{
		if (lst->cmd[i][0] == '$')
		{
			var = vardol(lst->cmd[i]);
			prtvar(var, shell);
		}
		else
		{
			lst->cmd[i] = ft_strtok(lst->cmd[i], "\"", 7);
			printf("%s", lst->cmd[i]);
			// if (lst->cmd[i + 1] && lst->cmd[i])
				// printf(" ");
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
	return (EXIT_SUCCESS);
}
