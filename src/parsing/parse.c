/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: misimon <misimon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/09 15:15:34 by stgerard          #+#    #+#             */
/*   Updated: 2023/03/07 17:15:56 by misimon          ###   ########.fr       */
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

t_bool	which_type(char *str, t_node *cmd)
{
	if (cmd->token[0] == 6)
		return (QUOTE);
	else if (cmd->token[0] == 5)
		return (DQUOTE);
	if (!ft_strcmp(str, "|"))
		return (PIPE);
	if (!ft_strcmp(str, ">") || !ft_strcmp(str, ">>"))
		return (OUTPUT_DIR);
	else if (!ft_strcmp(str, "<"))
		return (INPUT_DIR);
	else if ((cmd->path)
		|| !ft_strcmp(str, "export") || !ft_strcmp(str, "unset")
		|| !ft_strcmp(str, "exit"))
		return (CMD);
	if (cmd->prev && cmd->prev->type == CMD)
		return (UNDEFINED);
	return (UNDEFINED);
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

void	check_token_var(t_node *node, t_minishell *ms)
{
	size_t	i;

	if (!node || (node->type != UNDEFINED && node->type != DQUOTE))
		return ;
	if (node && node->token)
	{
		i = -1;
		while (node->token[++i])
		{
			if (node->token[i] == '$')
			{
				node->token = do_var_replacement(node->token, ms);
				i = -1;
			}
		}
	}
}

void	cmd_parsing(char *buf, t_minishell *ms)
{
	char	*temp;
	char	**token_tab;
	size_t	i;

	(void)ms;
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

// int	do_parse(t_node *cmd, t_minishell *ms)
// {
// 	cmd->token = ft_strtok(cmd->token, "\6\5", '\7');
// 	cmd->token = ft_strfjoin(ft_strfjoin(cmd->token, " "), cmd->next->token);
// 	delete_next(ms->cmd, cmd);
// 	i = 0;
// 	cmd = ms->cmd->head;
// 	return (i);
// }

// t_bool	which_parse(t_minishell *ms, t_node *c, size_t *i)
// {
// 	if (c->token[0] == '|')
// 		return (FALSE);
// 	if (c && c->next && c->type == CMD && (c->next->type != PIPE && c->next
//->type != CMD && c->next->type != INPUT_DIR && c->next->type != OUTPUT_DIR))
// 		*i = do_parse(c, ms, *i);
// 	else if (c && c->next && (c->type == 3 || c->type == 2) 
//			&& c->next->type == -1)
// 		*i = do_parse(c, ms, *i);
// 	else
// 		return (FALSE);
// 	return (TRUE);
// }

// void debug_parsing(t_minishell *ms)
// {
// 	t_node	*cmd;

// 	cmd = ms->cmd->head;
// 	while (cmd)
// 	{
// 		printf("\ndebug of %s\n", cmd->token);
// 		if (cmd->cmd && cmd->type == CMD)
// 		{
// 			for (int i = 0; cmd->cmd[i]; i++)
// 				printf("%s\n", cmd->cmd[i]);
// 		}
// 		else if (cmd->cmd && (cmd->type == INPUT_DIR 
//				|| cmd->type == OUTPUT_DIR))
// 			printf("Output or Input\n");
// 		else
// 			printf("Pipe\n");
// 		write(1, "\n", 1);
// 		cmd = cmd->next;
// 	}	
// }
