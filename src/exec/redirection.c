/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: misimon <misimon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 16:56:59 by misimon           #+#    #+#             */
/*   Updated: 2023/03/13 17:42:09 by misimon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	define_input(t_minishell *ms)
{
	t_node	*node;
	char	*str;

	node = ms->cmd->tail;
	while (node)
	{
		if (node->type == INPUT_DIR && node->cmd && node->cmd[1]
			&& !ft_strcmp(node->cmd[0], "<<"))
		{
			ms->new_fd[0] = open(node->cmd[1], O_RDWR | O_CREAT | O_TRUNC, 0777);
			str = readline("> ");
			while (str != NULL && ft_strcmp(str, node->cmd[1]) != 0)
			{
				ft_putstr_fd(str, ms->new_fd[0]);
				ft_putstr_fd("\n", ms->new_fd[0]);
				str = readline("> ");
			}
			close(ms->new_fd[0]);
			ms->new_fd[0] = open(node->cmd[1], O_RDONLY);
			break ;
		}
		else if (node->type == INPUT_DIR && node->cmd && node->cmd[1])
		{
			ms->new_fd[0] = open(node->cmd[1], O_RDONLY);
			break ;
		}
		node = node->prev;
		ms->new_fd[0] = 0;
	}	
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
			if (ms->new_fd[1] == -1)
				break ;
			dup2(ms->new_fd[1], STDOUT_FILENO);
			close(ms->new_fd[1]);
			break ;
		}
		else if (node->type == OUTPUT_DIR && node->cmd && node->cmd[1])
		{
			ms->new_fd[1] = open(node->cmd[1],
					O_CREAT | O_WRONLY | O_TRUNC, 0644);
			if (ms->new_fd[1] == -1)
				break ;
			dup2(ms->new_fd[1], STDOUT_FILENO);
			close(ms->new_fd[1]);
			break ;
		}
		node = node->prev;
		ms->new_fd[1] = 1;
	}
}

void	open_fd(t_minishell *ms)
{
	define_input(ms);
	define_output(ms);
}
