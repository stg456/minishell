/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: misimon <misimon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 16:46:01 by stgerard          #+#    #+#             */
/*   Updated: 2023/01/31 15:08:09 by misimon          ###   ########.fr       */
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

int	ft_pwd(t_node *lst)
{
	char	buffer[256];

	// (void)shell;
	if (lst->cmd[0] && !lst->cmd[1])
	{
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
	}
	else if (lst->cmd[0] && lst->cmd[1])
	{
		printf("pwd: too many arguments\n");
	}
	return EXIT_SUCCESS;
}

// parait bon

int		ft_echo(t_node *lst)
{
	int		i;

	i = 0;
	if (lst->cmd[0] && !lst->cmd[1])
	{
		printf("\n");
		return EXIT_SUCCESS;
	}
	if (ft_strcmp(lst->cmd[1], "-n") != 0)
	{
		i = 1;
		while (lst->cmd[i])
		{
			printf("%s", lst->cmd[i]);
			i++;
			if (lst->cmd[i])
				printf(" ");
		}
		printf("\n");
	}
	else if (ft_strcmp(lst->cmd[1], "-n") == 0)
	{
		i = 2;
		while (lst->cmd[i])
		{
			printf("%s", lst->cmd[i]);
			i++;
			if (lst->cmd[i])
				printf(" ");
		}
	}
	return EXIT_SUCCESS;
}

// parait bon

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