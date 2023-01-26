/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stgerard <stgerard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/01 10:48:01 by stgerard          #+#    #+#             */
/*   Updated: 2022/12/11 11:01:51 by stgerard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_len(int n)
{
	int	count;

	count = 0;
	if (n == 0)
		return (1);
	if (n < 0)
		count++;
	while (n)
	{
		n = n / 10;
		count++;
	}
	return (count);
}

static void	ft_tab(char *str, unsigned int n, int len)
{
	len = len - 1;
	while (n)
	{
		str[len] = (n % 10) + 48;
		n = n / 10;
		len--;
	}
}

char	*ft_itoa(int n)
{
	unsigned int	nb;
	char			*str;
	int				len;

	len = ft_len(n);
	str = malloc((len + 1) * sizeof(char));
	if (str == NULL)
		return (NULL);
	str[len] = '\0';
	if (n == 0)
		str[0] = '0';
	else if (n < 0)
	{
		str[0] = '-';
		n = -n;
		nb = n;
		ft_tab(str, nb, len);
	}
	else
	{
		nb = n;
		ft_tab(str, nb, len);
	}
	return (str);
}
