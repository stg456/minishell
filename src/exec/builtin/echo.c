/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stgerard <stgerard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 10:52:18 by stgerard          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2023/03/03 17:25:58 by stgerard         ###   ########.fr       */
=======
/*   Updated: 2023/03/03 17:28:39 by misimon          ###   ########.fr       */
>>>>>>> 790b402a19e37cf2a50958e404b49c0be4617fa5
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

void	affecho(t_node *lst, size_t	i)
{
<<<<<<< HEAD
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
	size_t	j;
	char	*nvar;

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
	printf("param = [%s]\n", param);
	if (param[1] == '$')
		j = 2;
	var = malloc(sizeof(char *) * ft_strlen(param));
	while (param[j])
	{
		if (param[j] != 7)
		{
			var[i] = param[j];
			i++;
			j++;
		}
		else
			j++;
	}
	var[i] = '\0';
	shell->status = 0;
	return (var);
}

void	affecho(t_node *lst, size_t	i, t_minishell *shell)
{
	// char	*var;
	size_t	j;

	j = 0;
	while (lst->cmd[++i])
	{
		// if (lst->cmd[i][0] == '\'')
		// {
		// 	// lst->cmd[i] = ft_strtok(lst->cmd[i], "\'", 7);
		// 	if (lst->cmd[i + 1])
		// 		printf(" ");
		// }
		// else if (lst->cmd[i][0] == '\"')
		// {
		// 	// lst->cmd[i] = ft_strtok(lst->cmd[i], "\"", 7);
		// 	var = vardol(lst->cmd[i], shell);
		// 	prtvar(var, shell);
		// 	shell->status = 0;
		// }
		// else if (lst->cmd[i][0] == '$' && lst->cmd[i][1] == '?')
		// {
		// 	wait(&shell->status);
		// 	printf("%d\n", shell->status);
		// 	shell->status = 0;
		// }
		// else if (lst->cmd[i][0] == '$')
		// {
		// 	var = vardol(lst->cmd[i], shell);
		// 	prtvar(var, shell);
		// 	shell->status = 0;
		// }
		// else
		// {
			// lst->cmd[i] = ft_strtok(lst->cmd[i], "\"", 7);
			printf("%s", lst->cmd[i]);
			if (lst->cmd[i + 1])
				printf(" ");
			(void)shell;
		// }
=======
	while (lst->cmd[++i])
	{
		printf("%s", lst->cmd[i]);
		if (lst->cmd[i + 1])
			printf(" ");
>>>>>>> 790b402a19e37cf2a50958e404b49c0be4617fa5
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
		affecho(lst, i);
		printf("\n");
	}
	else if (lst->cmd && lst->cmd[i] && ft_strcmp(lst->cmd[1], "-n") == 0)
		affecho(lst, ++i);
	shell->status = 0;
	return (shell->status);
}
