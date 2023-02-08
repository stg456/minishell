/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: misimon <misimon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 16:46:01 by stgerard          #+#    #+#             */
/*   Updated: 2023/02/08 16:13:33 by misimon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

// void	ft_exit(t_node *lst)
// {
// 	int		i;

// 	i = 0;
// 	if (lst->cmd[0] && !lst->cmd[1])
// 	{
// 		// free quelque chose
// 		// free le export ou le env et les variables
// 		return EXIT_SUCCESS;
// 	}
// 	else
// 		printf("exit: too many arguments\n");
// }

// parait bon, mais y'a clairement des trucs à revoir !!

int	ft_env(t_minishell *shell)
{
	size_t	i;
	int		j; // index sur les variables avec valeurs

	j = 0;
	i = -1;
	while (shell->env[++i])
		printf("%s\n", shell->env[i]);
	// while (shell->inenv->varvalue)
	// {
	// 	printf("%s\n", shell->inenv->varvalue[j++]);
	// }
	// while (shell->inenv->varvalue)
	// {
	// 	printf("%s\n", shell->inenv->varvalue[j]);
	// 	j++;
	// }
	return (EXIT_SUCCESS);	
}

// parait bon mais manque variables

int	ft_pwd(t_node *lst)
{
	char	buffer[256];

	if (lst->token && ((lst->next && !lst->next->is_cmd) || !lst->next))
	{
		if (getcwd(buffer, 256) == NULL)
		{
			perror("Cannot get current working directory path\n");
			if (errno == ERANGE)
				perror("Buffer size is too small.\n");
			exit(EXIT_FAILURE);
    	}
		printf("%s\n", buffer);
	}
	else if (lst->token && lst->next->is_cmd == TRUE)
		printf("pwd: too many arguments\n");
	return EXIT_SUCCESS;
}

// parait bon

int		ft_echo(t_node *lst)
{
	t_node *actual;

	if (lst->next)
		actual = lst->next;
	if (lst->token && ((lst->next && !lst->next->is_cmd) || !lst->next))
	{
		printf("\n");
		return EXIT_SUCCESS;
	}
	if (lst->next->token && ft_strcmp(lst->next->token, "-n") != 0)
	{
		while (actual && actual->is_cmd)
		{
			actual->token = ft_strtok(actual->token, "\"", 7);
			printf("%s", actual->token);
			actual = actual->next;
			if (actual && actual->is_cmd)
				printf(" ");
		}
		printf("\n");
	}
	else if (lst->next->token && ft_strcmp(lst->next->token, "-n") == 0)
	{
		actual = actual->next;
		while (actual && actual->is_cmd)
		{
			actual->token = ft_strtok(actual->token, "\"", 7);
			printf("%s", actual->token);
			actual = actual->next;
			if (actual && actual->is_cmd)
				printf(" ");
		}
	}
	return EXIT_SUCCESS;
}

// parait bon mais manque le $

// int	ft_unset(char *buf)
//  {
	
//  }

// que dalle

int	ft_cd(t_minishell *shell, t_node *lst)
{
	int		i;

	shell->dir = getenv("PWD=");
	if (lst->token && ((lst->next && !lst->next->is_cmd) || !lst->next))
	{
		shell->dir = getenv("HOME=");
		chdir(shell->dir);
	}
	else if (lst->token && (lst->next && lst->next->is_cmd))
	{
		i = chdir(lst->next->token);
		if (i == 0)
		{
			shell->dir = ft_strjoin(lst->token, " ");
			shell->dir = ft_strjoin(shell->dir, lst->next->token);
		}
		chdir(shell->dir);
	}
	return 0;
}

// manque le ~ 
// parait bon !!!