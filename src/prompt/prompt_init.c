/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: misimon <misimon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 17:35:40 by misimon           #+#    #+#             */
/*   Updated: 2023/03/13 20:22:03 by misimon          ###   ########.fr       */
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

char	**env_init(void)
{
	char		**tab;
	extern char	**environ;
	size_t		i;

	tab = malloc(sizeof(char *) * ft_tablen(environ) + 1);
	if (!tab)
		return (NULL);
	i = 0;
	while (environ[i])
	{
		tab[i] = ft_strdup(environ[i]);
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

t_minishell	*sh_init(void)
{
	t_minishell	*sh;

	sh = malloc(sizeof(t_minishell));
	if (!sh)
		return (NULL);
	sh->cmd = create_list();
	sh->env = env_init();
	sh->path = ft_split(getenv("PATH"), ':');
	if (check_all_create(sh) == FALSE)
		return (NULL);
	sh->status = 0;
	sh->new_fd[0] = 0;
	sh->new_fd[1] = 1;
	return (sh);
}
