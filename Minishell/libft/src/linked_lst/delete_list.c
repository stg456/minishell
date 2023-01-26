/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delete_list.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: misimon <misimon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 15:39:50 by misimon           #+#    #+#             */
/*   Updated: 2022/11/09 15:54:15 by misimon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libft.h"

void	delete_all_list(t_list *ptr)
{
	t_node	*tmp_node;
	t_node	*node;

	node = ptr->head;
	while (node)
	{
		tmp_node = node;
		node = node->next;
		free(tmp_node);
	}
	ptr->head = NULL;
	ptr->tail = NULL;
	ptr->size = 0;
}

void	clear_list(t_list *ptr)
{
	if (ptr->head != NULL || ptr->tail != NULL)
		delete_all_list(ptr);
	free(ptr);
}

void	delete_last(t_list *ptr)
{
	t_node	*node;

	node = ptr->tail;
	if (!node)
		exit (EXIT_FAILURE);
	ptr->tail = node->prev;
	if (ptr->tail)
		ptr->tail->next = NULL;
	else
		ptr->head = NULL;
	free(node);
	ptr->size--;
}

void	delete_first(t_list *ptr)
{
	t_node	*node;

	node = ptr->head;
	if (!node)
		exit(EXIT_FAILURE);
	ptr->head = node->next;
	if (ptr->head)
		ptr->head->prev = NULL;
	else
		ptr->head = NULL;
	free(node);
	ptr->size--;
}
