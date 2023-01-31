/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stgerard <stgerard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 16:46:01 by stgerard          #+#    #+#             */
/*   Updated: 2023/01/31 16:25:56 by stgerard         ###   ########.fr       */
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
			lst->cmd[i] = ft_strtok(lst->cmd[i], "\"");
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
			lst->cmd[i] = ft_strtok(lst->cmd[i], "\"");
			printf("%s", lst->cmd[i]);
			i++;
			if (lst->cmd[i])
				printf(" ");
		}
	}
	return EXIT_SUCCESS;
}

// parait bon

int	ft_export(t_node *lst)
{
	char	*var;
	char	*value;
	int		i;
	int		j;
	int		k;

	value = NULL;
	var = NULL;
	i = 0;
	j = 0;
	k = 0;
	if (lst->cmd[0] && !lst->cmd[1])
	{
		printf("\n"); // pas ca, doit afficher tout
		return EXIT_SUCCESS;
	}
	// printf("a");
	if (lst->cmd[0] && lst->cmd[1])
	{
		printf("%s\n", lst->cmd[1]);
		while (lst->cmd[1])
		{
			while (lst->cmd[1][i] != '=')
			{
				printf("b");
				var[j] = lst->cmd[1][i];
				printf("%s\n", var);
				i++;
				j++;
			}
		}
		i += 2;
		while (lst->cmd[1][i])
		{
			printf("c");
			value[k] = lst->cmd[1][i];
			i++;
			k++;
		}
		printf("d");
	}
	printf("var:%s value:%s\n", var, value);
	return 1;
}

 // export a=1 : seg fault !!!


// int	ft_unset(char *buf)
//  {
	
//  }