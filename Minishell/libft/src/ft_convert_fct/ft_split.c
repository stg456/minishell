/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: misimon <misimon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/14 09:24:46 by misimon           #+#    #+#             */
/*   Updated: 2022/11/07 18:32:51 by misimon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libft.h"

size_t	wordcount(const char *str, char c)
{
	size_t	i;
	size_t	i2;

	i2 = 0;
	i = 0;
	while (str[i])
	{
		if (str[i] != c)
			i2++;
		while (str[i] != c && str[i + 1])
			i++;
		i++;
	}
	return (i2);
}

size_t	wordl(const char *str, char c)
{
	size_t	i;
	size_t	len;

	i = 0;
	len = 0;
	while (str[i] == c)
		i++;
	while (str[i] != c && str[i++])
		len++;
	return (len);
}

char	**ft_split(char const *s, char c)
{
	char	**tab_str;
	size_t	i[3];

	i[0] = -1;
	i[2] = 0;
	if (!s)
		return (NULL);
	tab_str = (char **)malloc(sizeof(char *) * (wordcount(s, c) + 1));
	if (!tab_str)
		return (NULL);
	while (++i[0] < wordcount((char *)s, c))
	{
		tab_str[i[0]] = (char *)malloc(sizeof(char) * (wordl(&s[i[2]], c) + 1));
		if (!(tab_str[i[0]]))
			return (NULL);
		i[1] = 0;
		while (s[i[2]] == c)
			i[2]++;
		while (s[i[2]] != c && s[i[2]])
			tab_str[i[0]][i[1]++] = s[i[2]++];
		tab_str[i[0]][i[1]] = '\0';
	}
	tab_str[i[0]] = NULL;
	return (tab_str);
}
