/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: misimon <misimon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 16:56:59 by misimon           #+#    #+#             */
/*   Updated: 2023/03/13 20:24:14 by misimon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	do_hdoc(t_minishell *ms, t_node *node)
{
	char	*str;

	ms->new_fd[0] = open(node->cmd[1], O_RDWR | O_CREAT | O_TRUNC, 0777);
	str = readline("> ");
	while (str != NULL && ft_strcmp(str, node->cmd[1]) != 0)
	{
		ft_putstr_fd(str, ms->new_fd[0]);
		ft_putstr_fd("\n", ms->new_fd[0]);
		str = readline("> ");
	}
	close(ms->new_fd[0]);
}

void	define_input(t_minishell *ms)
{
	t_node	*node;

	node = ms->cmd->tail;
	while (node)
	{
		if (node->type == INPUT_DIR && node->cmd && node->cmd[1]
			&& !ft_strcmp(node->cmd[0], "<<"))
		{
			do_hdoc(ms, node);
			ms->new_fd[0] = open(node->cmd[1], O_RDONLY);
			break ;
		}
		else if (node->type == INPUT_DIR && node->cmd && node->cmd[1])
		{
			ms->new_fd[0] = open(node->cmd[1], O_RDONLY);
			if (ms->new_fd[0] == -1)
			{
				printf("Minishell: %s: ", node->cmd[1]);
				printf("No such file or directory !\n");
			}
			break ;
		}
		node = node->prev;
		ms->new_fd[0] = 0;
	}	
}

t_bool	do_dup(t_minishell *ms)
{
	if (ms->new_fd[1] == -1)
		return (FALSE);
	dup2(ms->new_fd[1], STDOUT_FILENO);
	close(ms->new_fd[1]);
	return (TRUE);
}

void	define_output(t_minishell *ms)
{
	t_node	*node;

	node = ms->cmd->tail;
	while (node)
	{
		if (node->type == OUTPUT_DIR && node->cmd && node->cmd[1]
			&& !ft_strcmp(node->cmd[0], ">>"))
		{
			ms->new_fd[1] = open(node->cmd[1],
					O_CREAT | O_WRONLY | O_APPEND, 0644);
			do_dup(ms);
			break ;
		}
		else if (node->type == OUTPUT_DIR && node->cmd && node->cmd[1])
		{
			ms->new_fd[1] = open(node->cmd[1],
					O_CREAT | O_WRONLY | O_TRUNC, 0644);
			do_dup(ms);
			break ;
		}
		node = node->prev;
		ms->new_fd[1] = 1;
	}
}

void	open_fd(t_minishell *ms)
{
	t_node	*node;

	ms->old_fd[0] = dup(STDIN_FILENO);
	ms->old_fd[1] = dup(STDOUT_FILENO);
	node = ms->cmd->head;
	while (node)
	{
		if (node->type == INPUT_DIR || node->type == OUTPUT_DIR)
		{
			if (node->cmd && !node->cmd[1])
			{
				printf("Minishell: syntax error near ");
				printf("unexpected token \'newline\' !\n");
				ms->new_fd[0] = -1;
				ms->new_fd[1] = -1;
			}
		}
		node = node->next;
	}
	if (ms->new_fd[0] != -1 || ms->new_fd[1] != -1)
	{
		define_input(ms);
		define_output(ms);
	}
}
