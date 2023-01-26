/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stgerard <stgerard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/21 14:15:11 by stgerard          #+#    #+#             */
/*   Updated: 2022/03/03 13:21:44 by stgerard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	size_t			i;
	unsigned char	*ptrdst;
	unsigned char	*ptrsrc;

	i = 0;
	ptrdst = (unsigned char *)dst;
	ptrsrc = (unsigned char *)src;
	if (!dst && !src)
		return (dst);
	while (i < n)
	{
		ptrdst[i] = ptrsrc[i];
		i++;
	}
	return (dst);
}
