/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: misimon <misimon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/09 15:15:34 by stgerard          #+#    #+#             */
/*   Updated: 2023/01/29 17:47:44 by misimon          ###   ########.fr       */
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

void	cmd_parsing(char *buf, t_minishell *shell)
{
	char	*str;
	char	**tab;
	size_t	i;
	size_t	i2;

	(void)shell;
	i = 0;
	str = ft_strtok(buf, "<>&|");
	tab = ft_split(str, 7);
	while (tab[i])
	{
		add_tail(shell->cmd, ft_split(tab[i], ' '));
		i2 = -1;
		while (shell->cmd->tail->cmd[++i2])
			printf("%s ", shell->cmd->tail->cmd[i2]);
		printf("\n");
		i++;
	}
	printf("END OF ALL CMD !\n");
}

/*
	Update du parsing :
	- Ajout des fonctions pour les linked list.
	- Début du parsing dans son fonctionnement
*/