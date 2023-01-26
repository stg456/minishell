/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stgerard <stgerard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/16 14:42:25 by stgerard          #+#    #+#             */
/*   Updated: 2023/01/25 16:27:24 by stgerard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	if (ft_strlen(s1) != ft_strlen(s2))
		return (0);
	while (s1[i] == s2[i] && s1[i] != '\0' && s2[i] != '\0')
		i++;
	if ((s1[i] - s2[i]) != 0)
		return (0);
	return (1);
}

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
