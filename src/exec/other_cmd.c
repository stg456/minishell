/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   other_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stgerard <stgerard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/06 17:42:16 by misimon           #+#    #+#             */
/*   Updated: 2023/03/01 17:03:33 by stgerard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	which_cmd_fork(t_node *cmd, t_minishell *ms)
{
	close(cmd->fd[0]);
	if (cmd && cmd->type == CMD)
	{
		if (ft_strcmp(cmd->cmd[0], "pwd") == 0)
			ft_pwd(cmd, ms);
		else if (ft_strcmp(cmd->cmd[0], "echo") == 0)
			ft_echo(cmd, ms);
		else
			execve(cmd->path, cmd->cmd, ms->cmd->all_path);
	}
	exit(1);
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

void	count_all(t_list *list, size_t *nbr_pipe, size_t *nbr_cmd)
{
	t_node	*actual;

	if (!list || !list->head || !list->tail)
		return ;
	actual = list->head;
	while (actual)
	{
		if (actual->type == PIPE)
			*nbr_pipe += 1;
		if (actual->type == CMD)
			*nbr_cmd += 1;
		actual = actual->next;
	}
}

void	do_multiple_pipe(t_minishell *ms, t_node *cmd, int input)
{
	pid_t	id;

	pipe(cmd->fd);
	id = fork();
	if (id == 0)
	{
		dup2(input, STDIN_FILENO);
		if (cmd->next)
			dup2(cmd->fd[1], STDOUT_FILENO);
		which_cmd_fork(cmd, ms);
	}
	else
	{
		dup2(cmd->fd[0], input);
		close(cmd->fd[1]);
		waitpid(id, &ms->status, 0);
	}
}	

void	other_cmd(t_minishell *ms)
{
	char	*path;
	t_node	*cmd;
	int		tmp_input;

	count_all(ms->cmd, &ms->cmd->nbr_pipe, &ms->cmd->nbr_cmd);
	path = getenv("PATH");
	ms->cmd->all_path = ft_split(path, ':');
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
			ms->status = 1;
			return ;
		}
		cmd = cmd->next;
	}
	return ;
}
