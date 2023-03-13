/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: misimon <misimon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 20:14:06 by misimon           #+#    #+#             */
/*   Updated: 2023/03/13 20:28:41 by misimon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

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
