/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: misimon <misimon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/16 13:40:28 by misimon           #+#    #+#             */
/*   Updated: 2022/11/07 18:32:51 by misimon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libft.h"

int	ft_p_char(int c)
{
	write(1, &c, 1);
	return (1);
}

int	ft_p_str(char *str)
{
	if (!str)
	{
		ft_putstr_fd("(null)", 1);
		return (6);
	}
	else
		ft_putstr_fd(str, 1);
	return (ft_strlen(str));
}

int	ft_p_putnbr(int n, int p_len)
{
	char	*str;

	str = ft_itoa(n);
	p_len += ft_p_str(str);
	free(str);
	return (p_len);
}

int	ft_p_args(const char str, va_list args)
{
	int	p_len;

	p_len = 0;
	if (str == 'c')
		p_len += ft_p_char(va_arg(args, int));
	else if (str == 's')
		p_len += ft_p_str(va_arg(args, char *));
	else if (str == 'p')
		p_len = ft_p_ptr(va_arg(args, unsigned long), p_len);
	else if (str == 'd' || str == 'i')
		p_len = ft_p_putnbr(va_arg(args, int), p_len);
	else if (str == 'u')
		p_len = ft_p_unsigned(va_arg(args, unsigned int), p_len);
	else if (str == 'x' || str == 'X')
		p_len = ft_p_hex(va_arg(args, unsigned int), p_len, str);
	else if (str == '%')
		p_len += write(1, "%", 1);
	return (p_len);
}

int	ft_printf(const char *str, ...)
{
	va_list	args;
	int		p_len;
	int		i;

	p_len = 0;
	i = 0;
	va_start(args, str);
	while (str[i])
	{
		if (str[i] == '%')
			p_len += ft_p_args(str[++i], args);
		else
			p_len += ft_p_char(str[i]);
		i++;
	}
	va_end (args);
	return (p_len);
}
