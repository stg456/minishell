/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stgerard <stgerard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 16:46:01 by stgerard          #+#    #+#             */
/*   Updated: 2023/01/30 17:05:57 by stgerard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

// void	ft_exit(t_minishell *shell)
// {

// }

int	ft_env(t_minishell *shell)
{
	size_t	i;

	i = 0;
	while (shell->env[i])
	{
		printf("%s\n", shell->env[i]);
		++i;
	}
	return (EXIT_SUCCESS);
}

// parait bon

int	ft_pwd(t_minishell *shell)
{
	char	buffer[256];

	(void)shell;
	if (getcwd(buffer, 256) == NULL)
	{
		perror("Cannot get current working directory path\n");
		if (errno == ERANGE)
		{
			perror("Buffer size is too small.\n");
		}
		exit(EXIT_FAILURE);
    }
	printf("%s\n", buffer);
	return EXIT_SUCCESS;
}

// doit remonter une erreur si il y a un argument en plus !!

int		ft_echo(t_node *lst)
{
	int		i;

	i = 0;
	if (!lst->cmd && !lst->cmd[1])
		return (-1);
	if (ft_strcmp(lst->cmd[1], "-n") != 0)
	{
		i = 0;
		while (lst->cmd[++i])
		{
			printf("%s ", lst->cmd[i]);
		}
		printf("\n");
	}
	else if (ft_strcmp(lst->cmd[1], "-n") == 0)
	{
		i = 1;
		while (lst->cmd[++i])
		{
			printf("%s", lst->cmd[i]);
		}
	}
	return EXIT_SUCCESS;
}

// echo seul seg fault
// gerer l'espace entre les arguments

int	ft_export(char *buf)
{
	char	*str;
	t_minishell	*shell; // mettre dedans
	char	*var;
	char	*value;
	int		i;
	int		j;

	(void)shell;
	value = NULL;
	var = NULL;
	if (!buf)
		return (EXIT_FAILURE);
	str = trimer("export", buf);
	if (!str)
		return (EXIT_FAILURE);
	i = 0;
	while (str[i] != '=')
	{
		var[i] = str[i];
	}
	i++;
	j = 0;
	while (str[i] != ' ')
	{
		value[j] = str[i];
	}
	// protections !!
	printf("var:%s value:%s\n", var, value);
	return 1;
}

 // pas encore bon mais logique

// int	ft_unset(char *buf)
//  {
	
//  }