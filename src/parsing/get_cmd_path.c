/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_cmd_path.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: misimon <misimon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/03 15:31:01 by misimon           #+#    #+#             */
/*   Updated: 2023/03/03 17:31:44 by misimon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	*cmd_path(t_minishell *sh)
{
	char	*path;
	char	*str;
	char	**all_path;
	t_bool	check;
	size_t	i;

	if (!access(sh->cmd->tail->token, F_OK))
		return (ft_strdup(sh->cmd->tail->token));
	check = FALSE;
	path = getenv("PATH");
	all_path = ft_split(path, ':');
	i = -1;
	while (all_path[++i])
	{
		str = ft_strfjoin(ft_strjoin(all_path[i], "/"), sh->cmd->tail->token);
		check = access(str, F_OK);
		if (check == 0)
			return (str);
	}
	free_tab(all_path);
	return (NULL);
}
