/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   other_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: misimon <misimon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/06 17:42:16 by misimon           #+#    #+#             */
/*   Updated: 2023/02/06 18:04:01 by misimon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

size_t count_pipe(t_list *list)
{
	size_t 	nbr_pipe;
	t_node	*actual;

	nbr_pipe = 0;
	if (!list || !list->head || !list->tail)
		return (0);
	actual = list->head;
	while (actual)
	{
		if (ft_strcmp(actual->token, "|") == 0)
			nbr_pipe++;
		actual = actual->next;
	}
	return (nbr_pipe);
}

void other_cmd(t_minishell *shell)
{
	size_t nbr_pipe;
	size_t i;

	nbr_pipe = count_pipe(shell->cmd);
	i = -1;
	while (++i < nbr_pipe)
		printf("create pipe %zu\n", i);
}
