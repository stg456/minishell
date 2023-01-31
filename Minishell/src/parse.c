/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: misimon <misimon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/09 15:15:34 by stgerard          #+#    #+#             */
/*   Updated: 2023/01/31 19:04:51 by misimon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*ft_strtok(char *str, char *delimiter)
{
	char	*result;
	size_t	i;

	if (!str)
		return (NULL);
	result = ft_strdup(str);
	i = -1;
	while (result[++i])
		if (ft_strchr(delimiter, result[i]))
			result[i] = 7;
	return (result);
}

char	*cmd_path(t_minishell *shell)
{
	char	*path;
	char	*str;
	char	**all_path;
	t_bool	check;
	size_t	i;

	check = FALSE;
	path = getenv("PATH");
	all_path = ft_split(path, ':');
	i = -1;
	while (all_path[++i] && check == FALSE)
	{
		str = ft_strjoin(ft_strjoin(all_path[i], "/"), shell->cmd->tail->cmd[0]);
		check = access(str, F_OK);
	}
	return (str);
}

t_bool	is_delimitor(char c)
{
	if (c == '>' || c == '<' || c == '|' || c == '&')
		return (TRUE);
	return (FALSE);
}

void	get_separator(char *buf, t_minishell *shell)
{
	size_t i;

	i = -1;
	while (buf[++i])
	{
		if (is_delimitor(buf[i]) == TRUE)
		{
			shell->cmd->tail->separator = malloc(sizeof(char) * 2);
			shell->cmd->tail->separator[0] = buf[i];
			shell->cmd->tail->separator[1] = '\0';
		}
	}
}

// petit problème concernant cette fonction par rapport au fait qu'il prendra forcément le dernier délimiteur

void	cmd_parsing(char *buf, t_minishell *shell)
{
	char	*str;
	char	**tab;
	size_t	i;

	(void)shell;
	str = ft_strtok(buf, "<>&|");
	tab = ft_split(str, 7);
	i = -1;
	while (tab[++i])
	{
		add_tail(shell->cmd, ft_split(tab[i], ' '));
		shell->cmd->tail->path = cmd_path(shell);
		get_separator(buf, shell);
		printf("%s\n", shell->cmd->tail->separator);
	}
}