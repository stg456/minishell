/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: misimon <misimon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/16 14:42:25 by stgerard          #+#    #+#             */
/*   Updated: 2023/03/13 20:20:53 by misimon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	set_default_fd(t_minishell *ms)
{
	dup2(ms->old_fd[0], STDIN_FILENO);
	close(ms->old_fd[0]);
	dup2(ms->old_fd[1], STDOUT_FILENO);
	close(ms->old_fd[1]);
}
