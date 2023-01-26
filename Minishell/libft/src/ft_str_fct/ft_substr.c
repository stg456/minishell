/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: misimon <misimon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/10 17:04:06 by misimon           #+#    #+#             */
/*   Updated: 2022/11/07 18:32:51 by misimon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*chr;
	size_t	i;
	size_t	i2;

	i = -1;
	i2 = -1;
	if (!s)
		return (NULL);
	chr = malloc(sizeof(*s) * (len + 1));
	if (!chr)
		return (NULL);
	while (s[++i2])
	{
		if (i2 >= start && ++i < len)
			chr[i] = s[i2];
	}
	chr[len] = '\0';
	return (chr);
}
