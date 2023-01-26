/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_islonglong.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stgerard <stgerard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/19 13:20:28 by stgerard          #+#    #+#             */
/*   Updated: 2022/12/11 11:02:37 by stgerard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_islonglong(const char *str)
{
	int			i;
	long long	rt;
	int			sign;

	rt = 0;
	i = 0;
	sign = 1;
	if (str[i] && (str[i] == '-' || str[i] == '+'))
	{
		if (str[i] == '-')
			sign *= -1;
		i++;
	}
	while (str[i] && str[i] >= '0' && str[i] <= '9')
	{
		rt = rt * 10 + (str[i] - 48);
		if (rt * sign > 2147483647)
			return (0);
		else if (rt * sign < -2147483648)
			return (0);
		i++;
	}
	return (1);
}
