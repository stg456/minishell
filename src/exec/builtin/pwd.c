/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stgerard <stgerard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 16:46:01 by stgerard          #+#    #+#             */
/*   Updated: 2023/03/07 13:46:37 by stgerard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

int	ft_pwd(t_node *lst, t_minishell *shell)
{
	char	buffer[256];

	if (lst->cmd && lst->cmd[0])
	{
		getcwd(buffer, 256);
		printf("%s\n", buffer);
	}
	shell->status = 0;
	return (shell->status);
}

// int	ft_pwd(t_node *lst, t_minishell *shell)
// {
// 	char	buffer[256];

// 	if (lst->cmd && lst->cmd[0])
// 	{
// 		if (getcwd(buffer, 256) == NULL)
// 		{
// 			perror("Cannot get current working directory path\n");
// 			if (errno == ERANGE)
// 				perror("Buffer size is too small.\n");
// 			shell->status = 0;
// 			exit(shell->status);
// 		}
// 		printf("%s\n", buffer);
// 	}
// 	shell->status = 0;
// 	return (shell->status);
// }