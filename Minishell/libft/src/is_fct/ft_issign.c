/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_issign.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: misimon <misimon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 03:32:27 by misimon           #+#    #+#             */
/*   Updated: 2022/11/09 14:47:12 by misimon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libft.h"

t_bool	ft_issign(char c)
{
	if (c == '+' || c == '-')
		return (TRUE);
	return (FALSE);
}
