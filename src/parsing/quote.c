/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: misimon <misimon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/15 17:23:03 by stgerard          #+#    #+#             */
/*   Updated: 2023/03/13 20:06:35 by misimon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	do_replace_quote(char *c, char set, size_t *i)
{
	*c = set;
	*i += 1;
}

char	*replace_quote_space(char *buf)
{
	size_t	quote;
	size_t	dquote;
	size_t	i;
	char	*new_buf;

	new_buf = ft_strdup(buf);
	if (!new_buf)
		return (0);
	free(buf);
	i = -1;
	quote = 0;
	dquote = 0;
	while (new_buf[++i])
	{
		if (ft_isspace(new_buf[i]) && (dquote % 2 || quote % 2))
			new_buf[i] = 4;
		if (new_buf[i] == '\'' && !(dquote % 2))
			do_replace_quote(&new_buf[i], 6, &quote);
		else if (new_buf[i] == '\"' && !(quote % 2))
			do_replace_quote(&new_buf[i], 5, &dquote);
	}
	return (new_buf);
}

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
		if (buf[i] == '\"' && !(quote % 2))
			dquote++;
		else if (buf[i] == '\'' && !(dquote % 2))
			quote++;
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
		else
			return (FALSE);
	}
	return (TRUE);
}
