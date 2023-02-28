/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: misimon <misimon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/15 17:23:03 by stgerard          #+#    #+#             */
/*   Updated: 2023/02/28 14:00:39 by misimon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

t_bool	check_quote(char *buf)
{
	size_t	i;
	size_t	dquote;
	size_t	quote;

	i = -1;
	dquote = 0;
	quote = 0;
	while (buf[++i])
	{
		if (buf[i] == '\"' && !quote % 2)
			dquote++;
		else if (buf[i] == '\'' && !dquote % 2)
			quote++;
	}
	if (dquote % 2 != 0 || quote % 2 != 0)
		return (TRUE);
	return (FALSE);
}

t_bool	check_quote_replace(char *buf)
{
	size_t	i;
	size_t	dquote;
	size_t	quote;

	i = -1;
	dquote = 0;
	quote = 0;
	while (buf[++i])
	{
		if (buf[i] == '\"' && !quote % 2)
			dquote++;
		else if (buf[i] == '\'' && !dquote % 2)
			quote++;
		if (ft_isspace(buf[i]) == TRUE && (dquote == 1 || quote == 1))
			buf[i] == 7;
	}
	if (dquote % 2 != 0 || quote % 2 != 0)
		return (TRUE);
	return (FALSE);
}

t_bool	ft_in_quote(char **buf)
{
	char	*str;

	while (check_quote(*buf))
	{
		str = readline("> ");
		if (str)
			*buf = ft_strjoin(*buf, str);
	}
	return (TRUE);
}

	// while ((dquote % 2 || !dquote) || (quote % 2 || !quote))
	// {
	// 	str = readline("> ");
	// 	buf = ft_strfjoin(buf, str);
	// 	i = 0;
	// 	while (buf[i++])
	// 	{
	// 		if (buf[i] == '\"')
	// 			dquote++;
	// 		if (buf[i] == '\'')
	// 			quote++;
	// 	}
	// 	if (!dquote % 2 || !quote % 2)
	// 		return (TRUE);
	// }