/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stgerard <stgerard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/15 17:23:03 by stgerard          #+#    #+#             */
/*   Updated: 2023/02/15 16:26:30 by stgerard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	ft_in_quote(char *buf)
{
	int	i;
	int	cpt;

	i = 0;
	cpt = 0;
	while (buf[i++])
	{
		if ((buf[i] == 39) || (buf[i] == 34))
			cpt += 1;
	}
	if (cpt % 2 == 0)
	{
		return (1);
	}
	// heredoc
	return (0);
}