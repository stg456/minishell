/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: misimon <misimon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/11 14:47:42 by stgerard          #+#    #+#             */
/*   Updated: 2023/03/14 19:11:52 by misimon          ###   ########.fr       */
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

t_bool	check_cmd(t_minishell *ms)
{
	t_node	*node;

	node = ms->cmd->head;
	while (node)
	{
		if (node->type == UNDEFINED || node->type == DQUOTE
			|| node->type == QUOTE)
		{
			printf("Minishell: %s command not found !\n", node->token);
			ms->status = 127;
			return (TRUE);
		}
		node = node->next;
	}
	return (FALSE);
}

t_bool	check_exist(t_minishell *ms)
{
	size_t	i;

	i = 0;
	while (ms->env[i] && ms->env)
	{
		if (!ft_strncmp(ms->env[i], "PATH=", 5))
			return (FALSE);
		i++;
	}
	printf("Minishell: No such file or directory !\n");
	return (TRUE);
}

void	do_cmd(t_minishell *ms, char *buf)
{
	if (check_input(buf) == 1)
		add_history(buf);
	if (check_cmd(ms) == TRUE)
		return ;
	other_cmd(ms);
}

int	main(int ac, char **av, char **envp)
{
	t_minishell		*sh;
	char			*buf;

	(void)ac;
	(void)av;
	sh = sh_init(envp);
	while (1)
	{
		signal(SIGQUIT, SIG_IGN);
		signal(SIGINT, sigint_handler);
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
		if (buf && *buf)
			free(buf);
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