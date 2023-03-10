/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   other_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: misimon <misimon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/06 17:42:16 by misimon           #+#    #+#             */
/*   Updated: 2023/03/10 14:08:27 by misimon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	sighandler(int sig)
{
	(void)sig;
	write(1, "\n", 1);
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

void	open_fd(t_minishell *ms)
{
	t_node	*node;

	node = ms->cmd->head;
	while (node)
	{
		if (node->type == OUTPUT_DIR && node->cmd[1])
			ms->fd_out = open(node->cmd[1], O_WRONLY | O_TRUNC);
		else if (node->type == INPUT_DIR && node->cmd[1])
			ms->fd_in = open(node->cmd[1], O_RDONLY);
		node = node->next;
	}
}

void	do_multiple_pipe(t_minishell *ms, t_node *cmd, int input)
{
	pid_t	id;

	pipe(cmd->fd);
	id = fork();
	if (id == 0)
	{
		if (ms->fd_in != -1)
		{
			dup2(ms->fd_in, STDIN_FILENO);
		}
		else
			dup2(input, STDIN_FILENO);
		if (cmd->next)
			dup2(cmd->fd[1], STDOUT_FILENO);
		which_cmd_fork(cmd, ms);
	}
	else
	{
		signal(SIGINT, sighandler);
		dup2(cmd->fd[0], STDIN_FILENO);
		close(cmd->fd[1]);
		waitpid(id, &ms->status, 0);
		ms->status = WEXITSTATUS(ms->status);
		dup2(input, STDIN_FILENO);
		close(input);
	}
}

void	other_cmd(t_minishell *ms)
{
	char	*path;
	t_node	*cmd;
	int		tmp_input;

	path = getenv("PATH");
	ms->cmd->all_path = ft_split(path, ':');
	open_fd(ms);
	tmp_input = dup(STDIN_FILENO);
	cmd = ms->cmd->head;
	while (cmd)
	{
		if (cmd->type == CMD)
		{
			if (which_cmd_no_fork(cmd, ms) == FALSE)
				do_multiple_pipe(ms, cmd, tmp_input);
		}
		else if (cmd->type == UNDEFINED)
		{
			printf("Minishell: %s command not found !\n", cmd->token);
			ms->status = 127;
			return ;
		}
		cmd = cmd->next;
	}
}
