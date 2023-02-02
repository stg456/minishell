/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: misimon <misimon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/09 15:15:34 by stgerard          #+#    #+#             */
/*   Updated: 2023/02/02 16:55:44 by misimon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*ft_strtok(char *str, char *delimiter, char replace)
{
	char	*result;
	size_t	i;

	if (!str)
		return (NULL);
	result = ft_strdup(str);
	i = -1;
	while (result[++i])
		if (ft_strchr(delimiter, result[i]))
			result[i] = replace;
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
	while (all_path[++i])
	{
		str = ft_strfjoin(ft_strjoin(all_path[i], "/"), shell->cmd->tail->token);
		check = access(str, F_OK);
		if (check == 0)
			return (str);
	}
	return (NULL);
}

void	cmd_parsing(char *buf, t_minishell *shell)
{
	char	*str;
	char	**tab;
	size_t	i;

	(void)shell;
	str = ft_strtok(buf, " \t\n\r\v\f", 7);
	tab = ft_split(str, 7);
	i = -1;
	while (tab[++i])
	{
		add_tail(shell->cmd, tab[i]);
		if (ft_strcmp(tab[i], "|") == 0 || ft_strcmp(tab[i], "<") == 0
			|| ft_strcmp(tab[i], ">") == 0 || ft_strcmp(tab[i], ">>") == 0
			|| ft_strcmp(tab[i], "<<") == 0)
			shell->cmd->tail->is_cmd = FALSE;
		else
			shell->cmd->tail->is_cmd = TRUE;
		shell->cmd->tail->path = cmd_path(shell);
	}
	free_tab(tab);
}

	// tab = ft_split(str, 7);
	// i = -1;
	// while (tab[++i])
	// {
	// 	add_tail(shell->cmd, ft_split(tab[i], ' '));
	// 	shell->cmd->tail->path = cmd_path(shell);
	// }
	// t_node *actual = shell->cmd->head;
	// while (actual != NULL)
	// {
	// 	printf("%s | %d >> %s\n", actual->token, actual->is_cmd, actual->path);
	// 	actual = actual->next;
	// }