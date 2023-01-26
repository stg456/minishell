/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stgerard <stgerard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/04 18:28:47 by stgerard          #+#    #+#             */
/*   Updated: 2022/07/07 13:05:31 by stgerard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*get_next_line(int fd)
{
	char	*s;
	char	*c;

	s = malloc(10000);
	c = s;
	while (read(fd, c, 1) > 0 && *c++ != '\n')
		;
	if (c > s)
	{
		*c = 0;
		return (s);
	}
	else
	{
		free(s);
		return (NULL);
	}
}
