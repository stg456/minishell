/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   linked_list.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: misimon <misimon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/29 16:02:45 by misimon           #+#    #+#             */
/*   Updated: 2023/02/08 19:56:58 by misimon          ###   ########.fr       */
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

void	add_tail(t_list *ptr, char *cmd)
{
	t_node	*new_node;

	new_node = malloc(sizeof(t_node));
	if (!new_node)
		exit(EXIT_FAILURE);
	new_node->token = ft_strdup(cmd);
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
		free(tmp_node->token);
		free(tmp_node->path);
		if(tmp_node->cmd)
			free_tab(tmp_node->cmd);
		node = node->next;
		free(tmp_node);
	}
	ptr->head = NULL;
	ptr->tail = NULL;
	ptr->size = 0;
}

void	delete_last(t_list *ptr)
{
	t_node	*node;

	node = ptr->tail;
	if (!node)
		exit (EXIT_FAILURE);
	free(node->token);
	free(node->path);
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
	free(node->token);
	free(node->path);
	ptr->head = node->next;
	if (ptr->head)
		ptr->head->prev = NULL;
	else
		ptr->head = NULL;
	free(node);
	ptr->size--;
}

t_list *delete_position(t_list *ptr, size_t position)
{
	size_t i;
	t_node *actual;

	if(!ptr)
		return (NULL);
	i = 1;
	actual = ptr->head;
	while (actual && i <= position)
	{
		if (position == i)
		{
			if (actual->next == NULL)
				delete_last(ptr);
			else if (actual->prev == NULL)
				delete_first(ptr);
			else
			{
				actual->next->prev = actual->prev;
				actual->prev->next = actual->next;
				free(actual);
				ptr->size--;
			}
		}
		else
			actual = actual->next;
		i++;
	}
	return(ptr);
}
