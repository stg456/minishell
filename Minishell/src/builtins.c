/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stgerard <stgerard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 16:46:01 by stgerard          #+#    #+#             */
/*   Updated: 2023/02/02 17:49:31 by stgerard         ###   ########.fr       */
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
// 		exit (0);
// 	}
// 	else
// 		printf("exit: too many arguments\n");
// }

// parait bon, mais y'a clairement des trucs à revoir !!

int	ft_env(t_minishell *shell)
{
	size_t	i;

	i = -1;
	while (shell->env[++i])
		printf("%s\n", shell->env[i]);
	return (EXIT_SUCCESS);
}

// parait bon

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
		while (actual && actual->is_cmd && !actual->path)
		{
			actual->token = ft_strtok(actual->token, "\"", 7);
			printf("%s", actual->token);
			actual = actual->next;
			if (actual && actual->is_cmd && !actual->path)
				printf(" ");
		}
		printf("\n");
	}
	else if (lst->next->token && ft_strcmp(lst->next->token, "-n") == 0)
	{
		actual = actual->next;
		while (actual && actual->is_cmd && !actual->path)
		{
			actual->token = ft_strtok(actual->token, "\"", 7);
			printf("%s", actual->token);
			actual = actual->next;
			if (actual && actual->is_cmd && !actual->path)
				printf(" ");
		}
	}
	return EXIT_SUCCESS;
}

// parait bon

// int	ft_export(t_node *lst)
// {
// 	char	*var;
// 	char	*value;
// 	int		i;
// 	int		j;
// 	int		k;

// 	value = NULL;
// 	var = NULL;
// 	i = 0;
// 	j = 0;
// 	k = 0;
// 	if (lst->cmd[0] && !lst->cmd[1])
// 	{
// 		printf("\n"); // pas ca, doit afficher tout
// 		return EXIT_SUCCESS;
// 	}
// 	// printf("a");
// 	if (lst->cmd[0] && lst->cmd[1])
// 	{
// 		printf("%s\n", lst->cmd[1]);
// 		while (lst->cmd[1])
// 		{
// 			while (lst->cmd[1][i] != '=')
// 			{
// 				printf("b");
// 				var[j] = lst->cmd[1][i];
// 				printf("%s\n", var);
// 				i++;
// 				j++;
// 			}
// 		}
// 		i += 2;
// 		while (lst->cmd[1][i])
// 		{
// 			printf("c");
// 			value[k] = lst->cmd[1][i];
// 			i++;
// 			k++;
// 		}
// 		printf("d");
// 	}
// 	printf("var:%s value:%s\n", var, value);
// 	return 1;
// }

 // export a=1 : seg fault !!!


// int	ft_unset(char *buf)
//  {
	
//  }

// que dalle

int	ft_cd(t_minishell *shell, t_node *lst)
{
	int		i;

	shell->dir = getenv("PWD=");
	// printf("%s\n", shell->dir);
	if (lst->token && !lst->next->is_cmd && !lst->path)
	{
		shell->dir = getenv("HOME=");
		chdir(shell->dir);
		// printf("%s\n", shell->dir);
	}
	else if (lst->token && lst->next->is_cmd == TRUE && !lst->path)
	{
		i = chdir(lst->next->token);
		// printf("arg de cd: %s\n", lst->cmd[1]);
		if (i == 0)
		{
			shell->dir = ft_strjoin(lst->token, " ");
			shell->dir = ft_strjoin(shell->dir, lst->next->token);
		}
		chdir(shell->dir);
		// printf("%s\n", shell->dir);
	}
	return 0;
}

// parait bon !!!