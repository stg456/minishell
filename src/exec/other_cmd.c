/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   other_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: misimon <misimon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/06 17:42:16 by misimon           #+#    #+#             */
/*   Updated: 2023/03/13 17:42:44 by misimon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	sighandler(int sig)
{
	(void)sig;
	write(1, "\n", 1);
}

void	close_all(void)
{
	int	i;

	i = 0;
	while (i < 256)
	{
		close(i);
		i++;
	}
}

void	which_cmd_fork(t_node *cmd, t_minishell *ms)
{
	close(cmd->fd[0]);
	if (cmd && cmd->type == CMD)
	{
		if (ft_strcmp(cmd->cmd[0], "pwd") == 0)
			ms->status = ft_pwd(cmd, ms);
		else if (ft_strcmp(cmd->cmd[0], "echo") == 0)
			ms->status = ft_echo(cmd, ms);
		else
			execve(cmd->path, cmd->cmd, ms->cmd->all_path);
	}
	exit(ms->status);
}

t_bool	which_cmd_no_fork(t_node *cmd, t_minishell *ms)
{
	if (cmd && cmd->type == CMD)
	{
		if (ft_strcmp(cmd->cmd[0], "env") == 0)
			ft_env(cmd, ms);
		else if (ft_strcmp(cmd->cmd[0], "export") == 0)
			ft_export(cmd, ms);
		else if (ft_strcmp(cmd->cmd[0], "unset") == 0)
			ft_unset(cmd, ms);
		else if (ft_strcmp(cmd->cmd[0], "exit") == 0)
			ft_exit(cmd, ms);
		else if (ft_strcmp(cmd->cmd[0], "cd") == 0)
			ft_cd(ms, cmd);
		else
			return (FALSE);
	}
	return (TRUE);
}

void	do_multiple_pipe(t_minishell *ms, t_node *cmd, int tmp)
{
	pid_t	id;
	t_node	*node;

	pipe(cmd->fd);
	id = fork();
	(void)tmp;
	if (id == 0)
	{
		dup2(tmp, STDIN_FILENO);
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

void	other_cmd(t_minishell *ms)
{
	char	*path;
	t_node	*cmd;
	int		tmp[2];

	path = getenv("PATH");
	ms->cmd->all_path = ft_split(path, ':');
	tmp[0] = dup(STDIN_FILENO);
	tmp[1] = dup(STDOUT_FILENO);
	open_fd(ms);
	cmd = ms->cmd->head;
	while (cmd)
	{
		if (cmd->type == CMD)
		{
			if (which_cmd_no_fork(cmd, ms) == FALSE)
				do_multiple_pipe(ms, cmd, ms->new_fd[0]);
		}
		else if (cmd->type == UNDEFINED || cmd->type == DQUOTE || cmd->type == QUOTE)
		{
			printf("Minishell: %s command not found !\n", cmd->token);
			ms->status = 127;
			return ;
		}
		cmd = cmd->next;
	}
	dup2(tmp[0], STDIN_FILENO);
	close(tmp[0]);
	dup2(tmp[1], STDOUT_FILENO);
	close(tmp[1]);
}
