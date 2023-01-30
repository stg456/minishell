/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: misimon <misimon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/09 15:15:34 by stgerard          #+#    #+#             */
/*   Updated: 2023/01/30 16:09:03 by misimon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*ft_strtok(char *str, char *delimiter)
{
	char	*result;
	size_t	i;

	if (!str)
		return (NULL);
	result = ft_strdup(str);
	i = -1;
	while (result[++i])
		if (ft_strchr(delimiter, result[i]))
			result[i] = 7;
	return (result);
}

char	*cmd_path(t_minishell *shell)
{
	char	*path;
	char	*str;
	char	**all_path;
	t_bool	check;
	size_t	i;

	check = FALSE;
	path = getenv("PATH");
	all_path = ft_split(path, ':');
	i = -1;
	while (all_path[++i] && check == FALSE)
	{
		str = ft_strjoin(ft_strjoin(all_path[i], "/"), shell->cmd->tail->cmd[0]);
		check = access(str, F_OK);
	}
	return (str);
}

void	cmd_parsing(char *buf, t_minishell *shell)
{
	char	*str;
	char	**tab;
	size_t	i;

	(void)shell;
	str = ft_strtok(buf, "<>&|");
	tab = ft_split(str, 7);
	i = -1;
	while (tab[++i])
	{
		add_tail(shell->cmd, ft_split(tab[i], ' '));
		shell->cmd->tail->path = cmd_path(shell);
	}
}