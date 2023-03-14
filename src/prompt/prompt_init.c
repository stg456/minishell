/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: misimon <misimon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 17:35:40 by misimon           #+#    #+#             */
/*   Updated: 2023/03/14 19:02:30 by misimon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

size_t	ft_tablen(char **tab)
{
	size_t	i;

	i = 0;
	while (tab[i])
		i++;
	return (i);
}

char	**env_init(char **envp)
{
	char		**tab;
	size_t		i;

	tab = ft_calloc(sizeof(char *), ft_tablen(envp) + 1);
	if (!tab)
		return (NULL);
	i = 0;
	while (envp[i])
	{
		tab[i] = ft_strdup(envp[i]);
		i++;
	}
	return (tab);
}

t_bool	check_all_create(t_minishell *sh)
{
	if (!sh->cmd || !sh->env || !sh->path)
	{
		if (sh->cmd)
			free(sh->cmd);
		if (sh->env)
			free_tab(sh->env);
		if (sh->path)
			free_tab(sh->path);
		free(sh);
		return (FALSE);
	}
	return (TRUE);
}

t_minishell	*sh_init(char **envp)
{
	t_minishell	*sh;

	sh = malloc(sizeof(t_minishell));
	if (!sh)
		return (NULL);
	sh->cmd = create_list();
	sh->env = env_init(envp);
	sh->path = ft_split(getenv("PATH"), ':');
	if (check_all_create(sh) == FALSE)
		return (NULL);
	sh->status = 0;
	sh->new_fd[0] = 0;
	sh->new_fd[1] = 1;
	return (sh);
}
