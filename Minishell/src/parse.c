/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: misimon <misimon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/09 15:15:34 by stgerard          #+#    #+#             */
/*   Updated: 2023/02/13 21:19:43 by misimon          ###   ########.fr       */
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
	free_tab(all_path);
	return (NULL);
}

t_bool which_type(char *str, t_node *cmd)
{
	if (!ft_strcmp(str, "|"))
		return (PIPE);
	else if (!ft_strcmp(str, ">") || !ft_strcmp(str, ">>"))
		return (OUTPUT_DIR);
	else if (!ft_strcmp(str, "<") || !ft_strcmp(str, "<<"))
		return (INPUT_DIR);
	else if (cmd->path || !ft_strcmp(str, "export") || !ft_strcmp(str, "unset")
			|| !ft_strcmp(str, "exit"))
		return (CMD);
	return (UNDEFINED);
}

void next_parsing(t_minishell *ms)
{
	t_node	*cmd;
	size_t	i;

	i = 1;
	cmd = ms->cmd->head;
	while (cmd && i < ms->cmd->size)
	{
		if(cmd->next && cmd->type == CMD && cmd->next->type == UNDEFINED)
		{
			cmd->token = ft_strfjoin(ft_strjoin(cmd->token, " "), cmd->next->token);
			delete_position(ms->cmd, i + 1);
			i = 1;
			cmd = ms->cmd->head;
		}
		else
		{
			cmd = cmd->next;
			i++;
		}
	}
	cmd = ms->cmd->head;
	while (cmd)
	{
		if (cmd->type == CMD && cmd->token)
			cmd->cmd = ft_split(cmd->token, ' ');
		else
			cmd->cmd = NULL;
		cmd = cmd->next;
	}
}

void	cmd_parsing(char *buf, t_minishell *ms)
{
	char	*str;
	char	**tab;
	size_t	i;

	str = ft_strtok(buf, " \t\n\r\v\f", 7);
	tab = ft_split(str, 7);
	i = -1;
	while (tab[++i])
	{
		add_tail(ms->cmd, tab[i]);
		ms->cmd->tail->path = cmd_path(ms);
		ms->cmd->tail->type = which_type(ms->cmd->tail->token, ms->cmd->tail);
	}
	t_node *actual = ms->cmd->head;
	while (actual != NULL)
	{
		printf("===============\nCMD=%s\nTYPE=%d\nPATH=%s\n===============\n\n", actual->token, actual->type, actual->path);
		actual = actual->next;
	}
	next_parsing(ms);
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