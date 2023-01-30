/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   linked_list.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: misimon <misimon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/29 16:02:45 by misimon           #+#    #+#             */
/*   Updated: 2023/01/30 16:12:36 by misimon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_list	*create_list(void)
{
	t_list	*ptr;

	ptr = malloc(sizeof(t_list));
	if (!ptr)
		return (NULL);
	ptr->head = NULL;
	ptr->tail = NULL;
	ptr->size = 0;
	return (ptr);
}

void	add_tail(t_list *ptr, char **cmd)
{
	t_node	*new_node;

	new_node = malloc(sizeof(t_node));
	if (!new_node)
		exit(EXIT_FAILURE);
	new_node->cmd = cmd;
	new_node->prev = ptr->tail;
	new_node->next = NULL;
	if (ptr->tail)
		ptr->tail->next = new_node;
	else
		ptr->head = new_node;
	ptr->tail = new_node;
	ptr->size++;
}

void	delete_all_list(t_list *ptr)
{
	t_node	*tmp_node;
	t_node	*node;

	node = ptr->head;
	while (node)
	{
		tmp_node = node;
		free_tab(tmp_node->cmd);
		free(tmp_node->path);
		node = node->next;
		free(tmp_node);
	}
	ptr->head = NULL;
	ptr->tail = NULL;
	ptr->size = 0;
}
