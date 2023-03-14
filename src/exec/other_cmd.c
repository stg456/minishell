/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   other_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: misimon <misimon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/06 17:42:16 by misimon           #+#    #+#             */
/*   Updated: 2023/03/14 19:13:47 by misimon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	sighandler(int sig)
{
	if (sig == SIGQUIT)
		write(1, "Quit: 3", 7);
	(void)sig;
	write(1, "\n", 1);
}

void	link_next_cmd(t_node *cmd)
{
	t_node	*node;

	node = cmd->next;
	while (node)
	{
		if (node->next && node->next->type == CMD)
		{
			dup2(cmd->fd[1], STDOUT_FILENO);
			break ;
		}
		node = node->next;
	}
}

void	do_multiple_pipe(t_minishell *ms, t_node *cmd, int tmp)
{
	pid_t	id;

	pipe(cmd->fd);
	signal(SIGQUIT, sighandler);
	id = fork();
	(void)tmp;
	if (id == 0)
	{
		dup2(tmp, STDIN_FILENO);
		link_next_cmd(cmd);
		which_cmd_fork(cmd, ms);
	}
	else
	{
		signal(SIGINT, sighandler);
		dup2(cmd->fd[0], tmp);
		close(cmd->fd[1]);
		waitpid(id, &ms->status, 0);
		ms->status = WEXITSTATUS(ms->status);
	}
}

t_bool	do_cmd_in_loop(t_node *cmd, t_minishell *ms)
{
	if (cmd->type == CMD)
	{
		if (!which_cmd_no_fork(cmd, ms) && !check_exist(ms))
			do_multiple_pipe(ms, cmd, ms->new_fd[0]);
	}
	return (TRUE);
}

void	other_cmd(t_minishell *ms)
{
	char	*path;
	t_node	*cmd;

	path = getenv("PATH");
	ms->cmd->all_path = ft_split(path, ':');
	open_fd(ms);
	if (ms->new_fd[0] == -1 || ms->new_fd[1] == -1)
	{
		ms->new_fd[0] = 0;
		ms->new_fd[1] = 1;
		return ;
	}
	cmd = ms->cmd->head;
	while (cmd)
	{
		if (!do_cmd_in_loop(cmd, ms))
			return ;
		cmd = cmd->next;
	}
	set_default_fd(ms);
}
