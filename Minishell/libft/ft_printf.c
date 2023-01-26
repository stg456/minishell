/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stgerard <stgerard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/16 15:00:29 by stgerard          #+#    #+#             */
/*   Updated: 2022/07/05 15:23:26 by stgerard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include <stdarg.h>

static int	ft_format(const char format, va_list list)
{
	int	i;

	i = 0;
	if (format == 'c')
		i += ft_putchar(va_arg(list, int));
	else if (format == 's')
		i += ft_putstr(va_arg(list, char *));
	else if (format == 'p')
		i += ft_putptr(va_arg(list, unsigned long long));
	else if (format == 'i' || format == 'd')
		i += ft_putnbr(va_arg(list, int));
	else if (format == 'u')
		i += ft_putint_unsigned(va_arg(list, unsigned int));
	else if (format == 'x' || format == 'X')
		i += ft_itohex(va_arg(list, unsigned int), format);
	else if (format == '%')
		i += ft_putchar('%');
	return (i);
}

int	ft_printf(const char *format, ...)
{
	int			len;
	int			i;
	va_list		list;

	i = 0;
	len = 0;
	va_start(list, format);
	while (format[i])
	{
		if (format[i] == '%')
		{
			len += ft_format(format[i + 1], list);
			i++;
		}
		else
			len += ft_putchar(format[i]);
		i++;
	}
	va_end(list);
	return (len);
}
