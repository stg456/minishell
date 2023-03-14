/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_uint.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: misimon <misimon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/02 22:47:40 by misimon           #+#    #+#             */
/*   Updated: 2022/11/07 18:32:51 by misimon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libft.h"

int	ulen(unsigned int n)
{
	unsigned int	l;

	l = 0;
	if (n <= 0)
		l++;
	while (n != 0)
	{
		n = n / 10;
		l++;
	}
	return (l);
}

char	*ft_uitoa(unsigned int n)
{
	char				*str;
	unsigned int		le;
	long unsigned int	nb;

	nb = n;
	le = ulen(nb);
	str = malloc(sizeof(char) * le + 1);
	if (!str)
		return (NULL);
	str[le--] = '\0';
	if (nb == 0)
		str[0] = '0';
	while (nb > 0)
	{
		str[le--] = (nb % 10) + '0';
		nb = nb / 10;
	}
	return (str);
}

int	ft_p_unsigned(unsigned int n, int p_len)
{
	char	*str;

	if (n == 0)
		p_len += ft_p_char('0');
	else
	{
		str = ft_uitoa(n);
		p_len += ft_p_str(str);
		free(str);
	}
	return (p_len);
}
