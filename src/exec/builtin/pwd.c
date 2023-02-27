/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stgerard <stgerard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 16:46:01 by stgerard          #+#    #+#             */
/*   Updated: 2023/02/27 15:00:29 by stgerard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

int	ft_pwd(t_node *lst, t_minishell *shell)
{
	char	buffer[256];

	if (lst->cmd && lst->cmd[0])
	{
		if (getcwd(buffer, 256) == NULL)
		{
			perror("Cannot get current working directory path\n");
			if (errno == ERANGE)
				perror("Buffer size is too small.\n");
			shell->status = 0;
			exit(shell->status);
		}
		printf("%s\n", buffer);
	}
	shell->status = 0;
	return (shell->status);
}

// exit parait bon
// pour echo le $? pas parfait, ne s'actualise pas !
// affichage d'une variable dans env ou export pas conforme !!!
// manque le heredoc
// manque le cas des quotes non fermes pour echo
// odre alpha pour env

// echo it works donne itworks !
// echo '$a' devrait afficher $a !!
// setenv ne marche pas !
// cat puis ctrl-C donne Minishell> Minishell> !!