/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stgerard <stgerard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/09 16:07:12 by stgerard          #+#    #+#             */
/*   Updated: 2023/02/03 17:05:17 by stgerard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	sigint_handler(int sig_num)
{
	// printf("signal %d\n", sig_num);
	if (sig_num == 2)
	{
		// ft_putendl("");
		write(1, "", 1);
		rl_on_new_line();
		// rl_replace_line("", 0); // pb compil
		rl_redisplay();
		// exit (EXIT_SUCCESS);
	}
	else if (sig_num == 3)
	{
		// ft_exit;
		exit (EXIT_SUCCESS);
	}
	// printf("apres %d\n", sig_num);
}
// ^C fait ^D
// ^D seg fault ... again !!!
