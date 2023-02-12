/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   other_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: misimon <misimon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/06 17:42:16 by misimon           #+#    #+#             */
/*   Updated: 2023/02/12 18:46:40 by misimon          ###   ########.fr       */
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
		if (ft_strcmp(actual->token, "|") == 0)
			*nbr_pipe += 1;
		if (actual->is_cmd == TRUE)
			*nbr_cmd += 1;
		actual = actual->next;
	}
}

void other_cmd(t_minishell *shell)
{
	size_t nbr_pipe;
	size_t nbr_cmd;
	pid_t	id;
	char **all_path;
	char *path;
	// int fd[2];

	nbr_pipe = 0;
	nbr_cmd = 0;
	count_all(shell->cmd, &nbr_pipe, &nbr_cmd);
	path = getenv("PATH");
	all_path = ft_split(path, ':');
	id = fork();
	if (nbr_cmd == 1 && id == 0)
	{
		execve(shell->cmd->head->path ,shell->cmd->head->cmd, all_path);
	}
	wait(NULL);
	// free(path);
	// free_tab(all_path);
	return ;
}
