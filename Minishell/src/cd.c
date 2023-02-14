/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stgerard <stgerard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 20:52:59 by stgerard          #+#    #+#             */
/*   Updated: 2023/02/14 20:59:46 by stgerard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	recupcmd(t_minishell *shell, t_node *lst)
{
	(void) shell;
	char		*newcmd;
	size_t		i;
	size_t		j;

	i = 0;
	j = 0;
	while (lst->cmd[0][j] != '/' && lst->cmd[0][j] != '\0')
		i++;
	i++;
	newcmd = malloc(sizeof(char) * (i - 1));
	i += 2;
	while (j < i)
	{
		newcmd[j] = lst->cmd[0][i];
		printf("%c\n", lst->cmd[0][i]);
	}
	newcmd[j] = '\0';
	printf("%s\n", newcmd);
	chdir(newcmd);
}

int	ft_cd(t_minishell *shell, t_node *lst)
{
	size_t		i;
	size_t		j;

	i = 0;
	j = 0;
	if (lst->cmd && lst->cmd[j] && !lst->cmd[j + 1])
	{
		shell->dir = getenv("HOME=");
		chdir(shell->dir);
	}
	else if (lst->cmd && lst->cmd[j] && lst->cmd[++j] && !lst->cmd[j + 1])
	{
		printf("%c\n", lst->cmd[j][0]);
		if (lst->cmd[j][0] == '~' && !lst->cmd[j][1])
		{
			shell->dir = getenv("HOME=");
			chdir(shell->dir);
		}
		// else if (lst->cmd[j][0] == '~' && lst->cmd[j][1] == '/')
		// {
			// recupcmd(shell, lst);
		// 	i = chdir(lst->cmd[j]);
		// 	chdir(lst->token);
		// }
		i = chdir(lst->cmd[j]);
		if (i != 0 && lst->cmd[j][0] != '~')
			printf("cd: %s: No such file or directory\n", lst->cmd[j]);
		chdir(lst->token);
	}
	printf("%s\n", lst->token);
	return (0);
}

// le cas cd ~/minishell ne marche pas