/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: misimon <misimon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/03 15:40:49 by misimon           #+#    #+#             */
/*   Updated: 2023/03/13 20:22:09 by misimon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

size_t	var_len_start(char *str)
{
	size_t	i;

	i = 0;
	while (str[i] != '$' && str[i])
		i++;
	return (i);
}	

size_t	name_len(char *str)
{
	size_t	i;

	i = var_len_start(str) + 1;
	if (str[i] == '?')
		return (1);
	while ((ft_isalnum(str[i])) && str[i])
		++i;
	return (i - var_len_start(str) - 1);
}

char	*ft_strndup(char *s1, size_t n, size_t start)
{
	char	*chr;
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	if (!n || !s1)
		return (NULL);
	chr = malloc(sizeof(char) * (n + 1));
	if (!chr)
		return (NULL);
	while (s1[i] && j < n)
	{
		if (i >= start && s1[i])
		{
			chr[j] = s1[i];
			j++;
		}
		i++;
	}
	chr[j] = '\0';
	return (chr);
}
