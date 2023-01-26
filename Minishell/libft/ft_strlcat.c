/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stgerard <stgerard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/21 14:16:26 by stgerard          #+#    #+#             */
/*   Updated: 2022/03/03 10:06:43 by stgerard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	i;
	size_t	j;

	i = ft_strlen(dst);
	j = 0;
	if (dstsize == 0)
		return (ft_strlen(src));
	if (i > dstsize - 1)
		return (dstsize + ft_strlen(src));
	while ((i + j < dstsize - 1) && src[j])
	{
		dst[j + i] = src[j];
		j++;
	}
	dst[j + i] = '\0';
	return (i + ft_strlen(src));
}
