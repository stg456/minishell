/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stgerard <stgerard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/21 11:36:43 by stgerard          #+#    #+#             */
/*   Updated: 2022/03/24 16:28:08 by stgerard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_putchar(int c)
{
	write(1, &c, 1);
	return (1);
}

int	ft_putstr(char *str)
{
	int	i;

	i = 0;
	if (!str)
	{
		write(1, "(null)", 6);
		return (6);
	}
	while (str[i] != '\0')
	{
		write(1, &str[i], 1);
		i++;
	}
	return (i);
}

static int	ft_intlen(long n)
{
	int	len;

	len = 0;
	if (n == 0)
		return (1);
	if (n < 0)
	{
		n = n * -1;
		len++;
	}
	while (n > 0)
	{
		n = n / 10;
		len++;
	}
	return (len);
}

char	*ft_itoa(int n)
{
	int		i;
	char	*toreturn;
	long	nb;

	nb = n;
	i = ft_intlen(nb);
	toreturn = (char *)malloc(i * sizeof(char) + 1);
	if (!toreturn)
		return (0);
	toreturn[i--] = '\0';
	if (nb == 0)
		toreturn[0] = 48;
	if (nb < 0)
	{
		toreturn[0] = '-';
		nb = nb * -1;
	}
	while (nb)
	{
		toreturn[i] = 48 + (nb % 10);
		nb = nb / 10;
		i--;
	}
	return (toreturn);
}

int	ft_putnbr(int nb)
{
	int		i;
	char	*str;

	str = ft_itoa(nb);
	i = ft_putstr(str);
	free(str);
	return (i);
}
