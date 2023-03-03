/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: misimon <misimon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/11 14:47:42 by stgerard          #+#    #+#             */
/*   Updated: 2023/03/03 18:26:32 by misimon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	check_input(char *str)
{
	size_t	i;

	i = 0;
	if (!str)
		return (-1);
	if (str[0] == '\0')
		return (0);
	while (str[i])
	{
		if (ft_isascii(str[i]) == 1 && ft_isspace(str[i]) == 0)
			return (1);
		++i;
	}
	return (0);
}

void	do_cmd(t_minishell *shell, char *buf)
{
	if (check_input(buf) == 1)
		add_history(buf);
	other_cmd(shell);
}

int	main(void)
{
	t_minishell		*sh;
	char			*buf;

	signal(SIGINT, sigint_handler);
	signal(SIGQUIT, sigint_handler);
	sh = sh_init();
	buf = NULL;
	while (1)
	{
		if (buf)
			free(buf);
		buf = readline("Minishell$> ");
		if (!buf)
			return (EXIT_SUCCESS);
		if (ft_in_quote(&buf) == TRUE)
		{
			cmd_parsing(buf, sh);
			do_cmd(sh, buf);
			delete_all_list(sh->cmd);
		}
		else
			sh->status = 130;
	}
	return (0);
}

// void	ft_free_shell(t_minishell *shell)
// {
// 	close(shell->fd_in);
// 	close(shell->fd_out);

// 	// free les cellules du tableau
// 	// /!\ free le tableau

// 	free(shell->path);
// 	free(shell->env);
// 	free(shell);
// 	// free les cellules des tableaux
// 	// /!\ free les doubles tableaux
// }