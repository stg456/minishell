/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stgerard <stgerard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/09 16:07:12 by stgerard          #+#    #+#             */
/*   Updated: 2023/02/01 16:45:44 by stgerard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	sigint_handler(int sig_num)
{
	if (sig_num == SIGINT)
	{
		printf("%d", sig_num);
		write(1, "\n", 1);
		rl_on_new_line();
        // rl_replace_line("", 0);
        rl_redisplay();
		// (void) sig_num;
	}
	if (sig_num == SIGQUIT)
	{
		printf("%d", sig_num);
		// seg fault
		exit (0);
	}
	// else if (sig_num == SIGQUIT)
	// {
	// 	;
	// }
	// else if (sig_num == EOF)
	// {
	// 	;
	// }	
}

// ne marche pas, ^C fait ^D !!!
// ^D seg fault ... again !!!