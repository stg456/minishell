/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt_visual.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stgerard <stgerard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 18:14:33 by misimon           #+#    #+#             */
/*   Updated: 2023/02/23 16:10:37 by stgerard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	*prompt_visual(void)
{
	char	*user;
	char	*prompt;

	user = getenv("USER");
	if (user == NULL)
	{
		user = malloc(sizeof(char) * 13);
		if (user == NULL)
			exit(1);
		user = "[Minishell]$ ";
		return (user);
	}
	else
	{
		prompt = malloc(sizeof(char) * 1);
		prompt[0] = '[';
		prompt = ft_strfjoin(prompt, user);
		prompt = ft_strfjoin(prompt, "]$ ");
		return (prompt);
	}
}
