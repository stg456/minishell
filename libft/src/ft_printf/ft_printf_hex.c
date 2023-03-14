/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_hex.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: misimon <misimon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/19 08:42:50 by misimon           #+#    #+#             */
/*   Updated: 2022/11/07 18:32:51 by misimon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libft.h"

int	ft_hexlen(unsigned int hexl)
{
	int	i;

	i = 0;
	while (hexl != 0)
	{
		hexl = hexl / 16;
		i++;
	}
	return (i);
}

void	ft_puthex(unsigned int hexn, const char c)
{
	if (hexn >= 16)
	{
		ft_puthex(hexn / 16, c);
		ft_puthex(hexn % 16, c);
	}
	else
	{
		if (hexn < 10)
			ft_putchar_fd(hexn + '0', 1);
		else
		{
			if (c == 'x')
				ft_putchar_fd((hexn - 10) + 'a', 1);
			else
				ft_putchar_fd((hexn - 10) + 'A', 1);
		}
	}
}

int	ft_p_hex(unsigned int hexn, int p_len, const char c)
{
	if (!hexn)
		p_len += write(1, "0", 1);
	else
	{
		ft_puthex(hexn, c);
		p_len += ft_hexlen(hexn);
	}
	return (p_len);
}
