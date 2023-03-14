/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_parsing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: misimon <misimon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/03 15:08:28 by misimon           #+#    #+#             */
/*   Updated: 2023/03/14 18:41:25 by misimon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	*return_free(char *value, char *name)
{
	free(name);
	if (!value)
		return (NULL);
	return (value);
}

char	*get_env_var(char *name, t_minishell *ms)
{
	char	**env;
	char	*value;
	size_t	len;

	env = ms->env;
	if (!name)
		return (NULL);
	len = ft_strlen(name);
	if (ft_strcmp(name, "?") == 0)
	{
		value = ft_itoa(ms->status);
		return (return_free(value, name));
	}
	while (*env)
	{
		if (!ft_strncmp(*env, name, len) && (*env)[len] == '=')
		{
			value = ft_strdup(*env + len + 1);
			return (return_free(value, name));
		}
		env++;
	}
	return (NULL);
}

char	*which_join(char *str_start, char *var_name, char *str_end)
{
	char	*str;

	if (str_start && var_name && str_end)
		str = ft_strfjoin(ft_strfjoin(str_start, var_name), str_end);
	else if (str_start && var_name)
		str = ft_strfjoin(str_start, var_name);
	else if (var_name && str_end)
		str = ft_strfjoin(var_name, str_end);
	else if (str_start && str_end)
		str = ft_strfjoin(str_start, str_end);
	else if (str_start)
		str = ft_strdup(str_start);
	else if (var_name)
		str = ft_strdup(var_name);
	else if (str_end)
		str = ft_strdup(str_end);
	else
		str = NULL;
	return (str);
}

char	*do_var_replacement(char *str, t_minishell *ms)
{
	size_t	l[2];
	char	*str_end;
	char	*var_name;
	char	*str_start;

	if (!str)
		return (NULL);
	l[0] = var_len_start(str);
	l[1] = name_len(str);
	str_start = ft_strndup(str, l[0], 0);
	var_name = ft_strndup(str, l[1], l[0] + 1);
	str_end = ft_strdup(str + l[1] + l[0] + 1);
	var_name = get_env_var(var_name, ms);
	free(str);
	str = which_join(str_start, var_name, str_end);
	return (str);
}

void	check_token_var(t_node *node, t_minishell *ms)
{
	size_t	i;

	if (!node || (node->type != UNDEFINED && node->type != DQUOTE))
		return ;
	if (node && node->token)
	{
		i = -1;
		while (node->token[++i])
		{
			if (node->token[i] == '$')
			{
				node->token = do_var_replacement(node->token, ms);
				i = -1;
			}
		}
	}
}
