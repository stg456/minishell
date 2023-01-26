/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: misimon <misimon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/16 14:42:25 by stgerard          #+#    #+#             */
/*   Updated: 2023/01/26 15:57:40 by misimon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*trimecho(char *s1)
{
	int		i;
	int		end;
	int		start;
	char	*e = "echo";
	char	*str;

	if (!s1)
		return (0);
	start = 0;
	i = 0;
	while (s1[i] == e[i])
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
