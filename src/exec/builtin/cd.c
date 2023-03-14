/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: misimon <misimon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 20:52:59 by stgerard          #+#    #+#             */
/*   Updated: 2023/03/07 15:48:11 by misimon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

void	abst(t_minishell *shell, t_node *lst)
{
	size_t	i;

	i = 0;
	i = chdir(lst->cmd[1]);
	if (i != 0 && lst->cmd[1][0] != '~')
	{
		shell->status = 1;
		printf("cd: %s: No such file or directory\n", lst->cmd[1]);
	}
	chdir(lst->token);
}

void	direct(t_minishell *shell, t_node *lst)
{
	size_t		i;
	size_t		h;
	char		*str;

	i = 0;
	h = 0;
	str = malloc(sizeof(char) * ft_strlen(lst->cmd[1]) - 1);
	if (!str)
		return ;
	while (lst->cmd[1][i])
	{
		if (i > 1)
		{
			str[h] = lst->cmd[1][i];
			h++;
		}
		i++;
	}
	str[h] = '\0';
	chdir(str);
	free(str);
	shell->status = 0;
}

void	home(t_minishell *shell, t_node *lst)
{
	(void) lst;
	shell->dir = getenv("HOME=");
	chdir(shell->dir);
	return ;
}

void	change_pwd(t_minishell *shell)
{
	char	buffer[256];
	size_t	i;

	i = 0;
	getcwd(buffer, 256);
	while (shell->env[i])
	{
		if (!ft_strncmp("PWD=", shell->env[i], 4))
		{
			free(shell->env[i]);
			shell->env[i] = ft_strjoin("PWD=", buffer);
			break ;
		}
		i++;
	}
}

int	ft_cd(t_minishell *shell, t_node *lst)
{
	size_t		i;
	size_t		j;

	i = 0;
	j = 0;
	if (lst->cmd && lst->cmd[j] && !(lst->cmd[j + 1]))
	{
		home(shell, lst);
		shell->status = 0;
	}
	else if (lst->cmd && lst->cmd[j] && lst->cmd[++j] && !(lst->cmd[j + 1]))
	{
		if (lst->cmd[j][0] == '~' && !(lst->cmd[j][1]))
			home(shell, lst);
		else if (lst->cmd[j][0] == '~' && lst->cmd[j][1] == '/')
		{
			home(shell, lst);
			direct(shell, lst);
		}
		abst(shell, lst);
	}
	change_pwd(shell);
	return (shell->status);
}
