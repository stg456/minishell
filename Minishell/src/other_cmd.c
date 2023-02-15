/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   other_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: misimon <misimon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/06 17:42:16 by misimon           #+#    #+#             */
/*   Updated: 2023/02/14 21:50:37 by misimon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void count_all(t_list *list, size_t *nbr_pipe, size_t *nbr_cmd)
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

void	other_cmd(t_minishell *ms)
{
	pid_t	id;
	char	*path;
	size_t	i;
	int		*fd;

	count_all(ms->cmd, &ms->cmd->nbr_pipe, &ms->cmd->nbr_cmd);
	path = getenv("PATH");
	ms->cmd->all_path = ft_split(path, ':');
	i = -1;
	fd = malloc(sizeof(int) * (ms->cmd->nbr_pipe * 2));
	if (!fd)
		exit(0);
	while (++i < ms->cmd->nbr_pipe)
		if (pipe(fd + i * 2) < 0)
		{
			perror("can't pipe");
			exit(0);
		}
	t_node *ac = ms->cmd->head;
	size_t	input = 0;
	while (ac)
	{
		if (ac->type == CMD && ac->path)
		{
			id = fork();
			if (id == 0)
			{
				if (ac->next)
					dup2(fd[input + 1], STDOUT_FILENO);
				if (input != 0)
					dup2(fd[input - 2], STDIN_FILENO);
				for(size_t j = 0; j < ms->cmd->nbr_pipe * 2; j++)
					close(fd[j]);
				execve(ac->path, ac->cmd, ms->cmd->all_path);
			}
			else if (id < 0)
				exit(0);
			input++;
		}
		ac = ac->next;
	}
	for (size_t j = 0; j < ms->cmd->nbr_pipe * 2; j++)
		close(fd[j]);
	for (size_t j = 0; j < ms->cmd->nbr_pipe; j++)
		wait(NULL);
	return ;
}
