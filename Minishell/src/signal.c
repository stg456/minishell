/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stgerard <stgerard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/09 16:07:12 by stgerard          #+#    #+#             */
/*   Updated: 2023/02/06 15:56:38 by stgerard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	sigint_handler(int signum)
{
	// printf("signal %d\n", signum);
	if (signum == SIGINT)
	{
		write(1, "\n", 1);
		rl_on_new_line();
		// rl_replace_line("", 0); // pb compil
		rl_redisplay();
		// exit (EXIT_SUCCESS);
	}
	if (signum == SIGQUIT)
	{
		// signal(SIGSEGV, SIG_IGN);
		// ft_exit;
		printf("b");
		// write(1, "\n", 1);
		rl_on_new_line();
		// rl_replace_line("", 0); // pb compil
		rl_redisplay();
		exit (EXIT_SUCCESS);
	}
	// printf("apres %d\n", signum);
}
// ^C pas mal!!!
// ^D seg fault ... again !!!
