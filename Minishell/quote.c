/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stgerard <stgerard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/15 17:23:03 by stgerard          #+#    #+#             */
/*   Updated: 2023/01/15 18:24:50 by stgerard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_in_quote(char *c, int i)
{
	int		squote;
	int		dquote;

	squote = 0;
	dquote = 0;
	while ()
	{
		if (c[i] == '\'' && !dquote)
		{
			squote = 0;
		}
		else if (c[i] == '\"' && !squote)
		{
			dquote = 0;
		}
		if ()
	}
	


	return (0);
}