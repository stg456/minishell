/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stgerard <stgerard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 20:52:59 by stgerard          #+#    #+#             */
/*   Updated: 2023/02/15 18:56:46 by stgerard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

// char	*recupcmd(t_minishell *shell, t_node *lst)
// {
// 	(void) shell;
// 	char		*newcmd;
// 	size_t		i;
// 	size_t		j;

// 	i = 0;
// 	j = 0;
// 	newcmd = NULL;
// 	printf("lst: %s\n", lst);

// 	newcmd = malloc(sizeof(char) * (ft_strlen(lst->cmd)));
// 	printf("newcmd: %s\n", newcmd);
// 	i = 2;
// 	while (lst)
// 	{
// 		newcmd[j] = lst[i];
// 		i++;
// 		j++;
// 	}
// 	newcmd[j] = '\0';

// 	printf("a lst: %s\n", lst);
// 	printf("a newcmd: %s\n", newcmd);
// 	// chdir(lst);

// 	return (newcmd);
// } // quel bordel

void	home(t_minishell *shell, t_node *lst)
{
	(void) lst;

	shell->dir = getenv("HOME=");
	chdir(shell->dir);
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
	if (lst->cmd && lst->cmd[j] && !(lst->cmd[j + 1]))
		home(shell, lst);
	else if (lst->cmd && lst->cmd[j] && lst->cmd[++j] && !(lst->cmd[j + 1]))
	{
		if (lst->cmd[j][0] == '~' && !(lst->cmd[j][1]))
			home(shell, lst);
		// else if (lst->cmd[j][0] == '~' && lst->cmd[j][1] == '/')
		// {
		// 	home(shell, lst);

		// 	newcmd = recupcmd(lst->cmd[j]);
		// 	printf("newcmd: %s\n", newcmd);

		
		i = chdir(lst->cmd[j]);
		if (i != 0 && lst->cmd[j][0] != '~')
			printf("cd: %s: No such file or directory\n", lst->cmd[j]);
		chdir(lst->token);
	}
	return (0);
}

// le cas cd ~/minishell ne marche pas