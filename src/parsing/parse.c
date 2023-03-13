/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: misimon <misimon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/09 15:15:34 by stgerard          #+#    #+#             */
/*   Updated: 2023/03/13 20:01:58 by misimon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

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

t_bool	join_cmd(t_node *tmp, t_minishell *ms)
{
	if ((tmp->type == OUTPUT_DIR || tmp->type == INPUT_DIR)
		&& tmp->next->type != PIPE)
	{
		tmp->token = ft_strfjoin(tmp->token, " ");
		tmp->token = ft_strfjoin(tmp->token, tmp->next->token);
		delete_next(ms->cmd, tmp);
		return (TRUE);
	}
	else if (tmp->next->type != INPUT_DIR && tmp->next->type != OUTPUT_DIR
		&& tmp->next->type != PIPE && tmp->type != PIPE)
	{
		tmp->token = ft_strfjoin(tmp->token, " ");
		tmp->token = ft_strfjoin(tmp->token, tmp->next->token);
		delete_next(ms->cmd, tmp);
		return (TRUE);
	}
	return (FALSE);
}

void	do_cmd_join(t_minishell *ms)
{
	t_node	*cmd;
	t_node	*tmp;

	cmd = ms->cmd->head;
	while (cmd)
	{
		tmp = cmd;
		while (tmp && tmp->next)
		{
			if (tmp->type == PIPE)
				break ;
			else if (join_cmd(tmp, ms) == TRUE)
				;
			else
				tmp = tmp->next;
		}
		if (tmp && tmp->next)
			cmd = tmp->next;
		else
			cmd = NULL;
	}
}

void	next_parsing(t_minishell *ms)
{
	t_node	*cmd;
	size_t	i;
	size_t	j;

	i = 0;
	do_cmd_join(ms);
	cmd = ms->cmd->head;
	while (cmd)
	{
		j = -1;
		cmd->token = ft_strtok(cmd->token, "\5\6", ' ');
		if ((cmd->type == CMD || cmd->type == INPUT_DIR
				|| cmd->type == OUTPUT_DIR) && cmd->token)
			cmd->cmd = ft_split(cmd->token, ' ');
		else
			cmd->cmd = NULL;
		while (cmd->cmd && cmd->cmd[++j])
			cmd->cmd[j] = ft_strtok(cmd->cmd[j], "\4", ' ');
		cmd = cmd->next;
	}
}

void	cmd_parsing(char *buf, t_minishell *ms)
{
	char	*temp;
	char	**token_tab;
	size_t	i;

	temp = replace_quote_space(ft_strdup(buf));
	if (!temp)
		return ;
	temp = ft_strtok(temp, " \t\n\r\v\f", 7);
	token_tab = ft_split(temp, 7);
	free(temp);
	i = -1;
	while (token_tab[++i])
	{
		add_tail(ms->cmd, token_tab[i]);
		ms->cmd->tail->path = cmd_path(ms);
		ms->cmd->tail->type = which_type(ms->cmd->tail->token, ms->cmd->tail);
		check_token_var(ms->cmd->tail, ms);
	}
	next_parsing(ms);
	free_tab(token_tab);
}
