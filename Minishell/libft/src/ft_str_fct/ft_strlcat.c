/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: misimon <misimon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/01 15:05:12 by misimon           #+#    #+#             */
/*   Updated: 2022/11/07 18:32:51 by misimon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	i;
	size_t	i2;

	i = 0;
	while (dst[i] && i < dstsize)
		i++;
	i2 = i;
	if (dstsize > 0)
	{
		while (src[i - i2] != '\0' && i < dstsize - 1)
		{
			dst[i] = src[i - i2];
			i++;
		}
		if (i2 < dstsize)
			dst[i] = '\0';
	}
	return (ft_strlen(src) + i2);
}
