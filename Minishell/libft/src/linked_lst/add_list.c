/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_list.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: misimon <misimon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 15:52:26 by misimon           #+#    #+#             */
/*   Updated: 2022/11/09 15:53:54 by misimon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libft.h"

void	add_tail(t_list *ptr, void *data)
{
	t_node	*new_node;

	new_node = malloc(sizeof(t_node));
	if (!new_node)
		exit(EXIT_FAILURE);
	new_node->content = data;
	new_node->prev = ptr->tail;
	new_node->next = NULL;
	if (ptr->tail)
		ptr->tail->next = new_node;
	else
		ptr->head = new_node;
	ptr->tail = new_node;
	ptr->size++;
}

void	add_head(t_list *ptr, void *data)
{
	t_node	*new_node;

	new_node = malloc(sizeof(t_node));
	if (!new_node)
		exit(EXIT_FAILURE);
	new_node->content = data;
	new_node->prev = NULL;
	new_node->next = ptr->head;
	if (ptr->head)
		ptr->head->prev = new_node;
	else
		ptr->tail = new_node;
	ptr->head = new_node;
	ptr->size++;
}