/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stgerard <stgerard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 16:46:01 by stgerard          #+#    #+#             */
/*   Updated: 2023/01/27 11:18:37 by stgerard         ###   ########.fr       */
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
	(void)shell;
	char buffer[256];

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

int		ft_echo(char *buf)
{
	char	*res;

	if (!buf)
		return (-1);
	res = trimecho(buf);
	printf("%s\n", res);
	return EXIT_SUCCESS;
}

// pas encore le -n
// pas mal mais le trim ne free pas 

int	ft_export(char *buf)
{
	char	*str;
	t_minishell	*shell; // mettre dedans
	char	*var;
	char	*value;
	int		i;
	int		j;

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
	return 1;
}

 // pas encore bon mais logique