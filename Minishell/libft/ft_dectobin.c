/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dectobin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stgerard <stgerard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/25 13:37:44 by stgerard          #+#    #+#             */
/*   Updated: 2022/04/25 13:42:24 by stgerard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_dectobin(long long nb)
{
	int			i;
	int			rem;
	long long	bin;

	bin = 0;
	rem = 1;
	i = 1;
	while (nb != 0)
	{
		rem = nb % 2;
		nb /= 2;
		bin += rem * i;
		i *= 10;
	}
	return (bin);
}
