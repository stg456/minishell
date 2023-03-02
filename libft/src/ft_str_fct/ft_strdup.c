/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: misimon <misimon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/01 16:09:01 by misimon           #+#    #+#             */
/*   Updated: 2023/02/28 18:19:59 by misimon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libft.h"

char	*ft_strdup(const char *s1)
{
	char	*chr;
	int		i;

	i = 0;
	chr = malloc(sizeof(*chr) * (ft_strlen(s1) + 1));
	if (!(chr))
		return (NULL);
	while (s1[i])
	{
		chr[i] = (char)s1[i];
		i++;
	}
	chr[i] = '\0';
	return (chr);
}
