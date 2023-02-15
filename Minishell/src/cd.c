/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: misimon <misimon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 20:52:59 by stgerard          #+#    #+#             */
/*   Updated: 2023/02/15 18:35:22 by misimon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

// char	*recupcmd(t_minishell *shell, char *lst)
// {
// 	(void) shell;
// 	char		*newcmd;
// 	size_t		i;
// 	size_t		j;

// 	i = 0;
// 	j = 0;
// 	newcmd = NULL;
// 	printf("lst: %s\n", lst);
// 	// while (lst)
// 	// 	i++;
// 	printf("i: %zu", i);

// 	// newcmd = malloc(sizeof(char) * i - 1);
// 	printf("newcmd: %s\n", newcmd);
// 	i = 2;
// 	// while (lst)
// 	// {
// 	// 	newcmd[j] = lst[i];
// 	// 	j++;
// 	// 	i++;
// 	// }
// 	printf("a lst: %s\n", lst);
// 	printf("a newcmd: %s\n", newcmd);
// 	// chdir(lst);

// 	return (NULL);
// }

void	home(t_minishell *shell, t_node *lst)
{
	(void) lst;

	shell->dir = getenv("HOME=");
	chdir(shell->dir);
	printf("b\n");
	return ;
}

int	ft_cd(t_minishell *shell, t_node *lst)
{
	size_t		i;
	size_t		j;
	size_t		k;
	// char		*newcmd;

	i = 0;
	j = 0;
	k = i + 2;
	if (lst->cmd && lst->cmd[j] && !lst->cmd[j + 1])
		home(shell, lst);
	else if (lst->cmd && lst->cmd[j] && lst->cmd[++j] && !lst->cmd[j + 1])
	{
		if (lst->cmd[j][0] == '~' && !lst->cmd[j][1])
			home(shell, lst);
// 		else if (lst->cmd[j][0] == '~' && lst->cmd[j][1] == '/')
// 		{
// 			printf("a\n");
// 			home(shell, lst);
// 			printf("c\n");
// 			newcmd = recupcmd(shell, lst->cmd[j]); //

// 			printf("e\n");
// 		}
		// printf("%s\n", lst->cmd[j]);
		i = chdir(lst->cmd[j]);
		// printf("e cmd: %s\n", lst->cmd[j]);
		if (i != 0 && lst->cmd[j][0] != '~')
			printf("cd: %s: No such file or directory\n", lst->cmd[j]);
		// printf("s cmd: %s\n", lst->token);
		chdir(lst->token);
	}
	// printf("%s\n", lst->token);
	return (0);
}

// le cas cd ~/minishell ne marche pas
