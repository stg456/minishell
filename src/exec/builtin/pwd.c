/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: misimon <misimon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 16:46:01 by stgerard          #+#    #+#             */
/*   Updated: 2023/02/22 17:50:00 by misimon          ###   ########.fr       */
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
			exit(EXIT_FAILURE);
		}
		printf("%s\n", buffer);
	}
	shell->status = 0;
	return (EXIT_SUCCESS);
}

// exit parait bon
// pour echo le $? pas parfait, ne s'actualise pas !
// affichage d'une variable dans env ou export pas conforme !!!
// manque le heredoc
// manque le cas des quotes non fermes pour echo
// odre alpha pour env
