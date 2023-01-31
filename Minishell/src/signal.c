/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stgerard <stgerard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/09 16:07:12 by stgerard          #+#    #+#             */
/*   Updated: 2023/01/31 17:26:02 by stgerard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	sigint_handler(int sig_num)
{
	// if (sig_num == SIGINT)
	// {
	// 	;
	// }
	// else if (sig_num == SIGQUIT)
	// {
	// 	;
	// }
	// else if (sig_num == EOF)
	// {
	// 	;
	// }
	printf("%d", sig_num);
}
