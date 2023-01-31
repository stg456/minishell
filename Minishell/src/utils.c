/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stgerard <stgerard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/16 14:42:25 by stgerard          #+#    #+#             */
/*   Updated: 2023/01/31 15:43:10 by stgerard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*trimer(char *s1, char *buf)
{
	int		i;
	int		end;
	int		start;
	char	*str;

	if (!s1)
		return (0);
	start = 0;
	i = 0;
	while (s1[i] == buf[i])
		i++;
	while (s1[i] == ' ')
		i++;
	start = i;
	end = ft_strlen(s1);
	str = malloc(sizeof(*s1) * (end - start + 1));
	i = 0;
	if (!str)
		return (NULL);
	while (start < end)
		str[i++] = s1[start++];
	str[i] = 0;
	return (str);
}

// il faudra free !!!