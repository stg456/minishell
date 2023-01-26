/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stgerard <stgerard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/21 14:21:31 by stgerard          #+#    #+#             */
/*   Updated: 2022/03/03 16:17:58 by stgerard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi(const char *str)
{
	int			i;
	int			n;
	long int	j;

	i = 0;
	j = 0;
	n = 1;
	while (((str[i] >= '\t') && (str[i] <= '\r')) || (str[i] == ' '))
		i++;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			n *= -1;
		i++;
	}
	while ((str[i] >= '0') && (str[i] <= '9'))
	{
		if (j * n > 2147483647)
			return (-1);
		else if (j * n < -2147483648)
			return (0);
		j = (str[i] - '0') + (j * 10);
		i++;
	}
	return (j * n);
}
