/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stgerard <stgerard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/09 16:07:12 by stgerard          #+#    #+#             */
/*   Updated: 2023/02/05 17:32:47 by stgerard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	sigint_handler(int signum)
{
	// printf("signal %d\n", signum);
	if (signum == SIGINT)
	{
		printf("a");
		// ft_putendl("");
		// write(1, "\n", 1);
		rl_on_new_line();
		// rl_replace_line(); // pb compil
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
// ^C ne reagit que si on enter !!!
// ^D seg fault ... again !!!
