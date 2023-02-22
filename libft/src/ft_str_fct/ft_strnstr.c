/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: misimon <misimon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/07 16:36:20 by misimon           #+#    #+#             */
/*   Updated: 2022/11/07 18:32:51 by misimon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	i;
	size_t	l;

	if (!*needle)
		return ((char *)haystack);
	while (*haystack && len-- > 0)
	{
		if (*haystack == *needle)
		{
			l = len;
			i = 1;
			while (needle[i] && haystack[i] == needle[i] && l-- > 0)
				i++;
			if (!needle[i])
				return ((char *)haystack);
		}
		haystack++;
	}
	return (0);
}
