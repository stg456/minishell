/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_ptr.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: misimon <misimon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/17 15:46:57 by misimon           #+#    #+#             */
/*   Updated: 2022/11/07 18:32:51 by misimon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libft.h"

int	ft_ptrlen(unsigned long ptr)
{
	int	i;

	i = 0;
	while (ptr != 0)
	{
		ptr = ptr / 16;
		i++;
	}
	return (i);
}

void	ft_putptr(unsigned long ptr)
{
	if (ptr >= 16)
	{
		ft_putptr(ptr / 16);
		ft_putptr(ptr % 16);
	}
	else
	{
		if (ptr < 10)
			ft_putchar_fd(ptr + '0', 1);
		else
			ft_putchar_fd((ptr - 10) + 'a', 1);
	}
}

int	ft_p_ptr(unsigned long ptr, int p_len)
{
	p_len += write(1, "0x", 2);
	if (!ptr)
		p_len += write(1, "0", 1);
	else
	{
		ft_putptr(ptr);
		p_len += ft_ptrlen(ptr);
	}
	return (p_len);
}
