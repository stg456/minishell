/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: misimon <misimon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/09 15:15:34 by stgerard          #+#    #+#             */
/*   Updated: 2023/02/08 20:16:01 by misimon          ###   ########.fr       */
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

t_bool is_delimitor(char *str)
{
	if (ft_strcmp(str, "|") == 0 || ft_strcmp(str, "<") == 0
			|| ft_strcmp(str, ">") == 0 || ft_strcmp(str, ">>") == 0
			|| ft_strcmp(str, "<<") == 0)
			return (TRUE);
	return (FALSE);
}

void next_parsing(t_minishell *shell)
{
	t_node	*actual_cmd;
	size_t	i;

	i = 1;
	actual_cmd = shell->cmd->head;
	while (actual_cmd && i < shell->cmd->size)
	{
		if(actual_cmd->next && !is_delimitor(actual_cmd->token) && !is_delimitor(actual_cmd->next->token))
		{
			actual_cmd->token = ft_strfjoin(ft_strjoin(actual_cmd->token, " "), actual_cmd->next->token);
			delete_position(shell->cmd, i + 1);
			i = 1;
			actual_cmd = shell->cmd->head;
		}
		else
		{
			actual_cmd = actual_cmd->next;
			i++;
		}
	}
	actual_cmd = shell->cmd->head;
	while (actual_cmd)
	{
		if (actual_cmd->is_cmd == TRUE && actual_cmd->token != NULL)
			actual_cmd->cmd = ft_split(actual_cmd->token, ' ');
		actual_cmd = actual_cmd->next;
	}
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
		if (is_delimitor(tab[i]) == TRUE)
			shell->cmd->tail->is_cmd = FALSE;
		else
			shell->cmd->tail->is_cmd = TRUE;
		shell->cmd->tail->path = cmd_path(shell);
	}
	next_parsing(shell);
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