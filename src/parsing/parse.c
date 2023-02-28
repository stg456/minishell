/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: misimon <misimon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/09 15:15:34 by stgerard          #+#    #+#             */
/*   Updated: 2023/02/28 14:05:25 by misimon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	*ft_strtok(char *str, char *delimiter, char replace)
{
	char	*result;
	size_t	i;

	if (!str)
		return (NULL);
	result = ft_strdup(str);
	i = -1;
	while (result[++i])
		if (ft_strchr(delimiter, result[i]))
			result[i] = replace;
	return (result);
}

char	*cmd_path(t_minishell *shell)
{
	char	*path;
	char	*str;
	char	**all_path;
	t_bool	check;
	size_t	i;

	check = FALSE;
	path = getenv("PATH");
	all_path = ft_split(path, ':');
	i = -1;
	while (all_path[++i])
	{
		str = ft_strfjoin(ft_strjoin(all_path[i], "/"), shell->cmd->tail->token);
		check = access(str, F_OK);
		if (check == 0)
			return (str);
	}
	free_tab(all_path);
	return (NULL);
}

// t_bool	check_if_var(char *str)
// {
// 	size_t	i;

// 	i = -1;
// 	while (str[++i])
// 		if (str[i] == '$')
// 			return (TRUE);
// 	return (FALSE);
// }

t_bool	which_type(char *str, t_node *cmd)
{
	if (cmd->prev && cmd->prev->type == CMD)
		return (UNDEFINED);
	if (!ft_strcmp(str, "|"))
		return (PIPE);
	else if (!ft_strcmp(str, ">") || !ft_strcmp(str, ">>"))
		return (OUTPUT_DIR);
	else if (!ft_strcmp(str, "<") || !ft_strcmp(str, "<<"))
		return (INPUT_DIR);
	else if ((cmd->path && ft_strcmp(str, "..") > 0)
		|| !ft_strcmp(str, "export") || !ft_strcmp(str, "unset")
		|| !ft_strcmp(str, "exit"))
		return (CMD);
	return (UNDEFINED);
}

void debug_parsing(t_minishell *ms)
{
	t_node	*cmd;

	cmd = ms->cmd->head;
	while (cmd)
	{
		printf("\ndebug of %s\n", cmd->token);
		if (cmd->cmd && cmd->type == CMD)
		{
			for (int i = 0; cmd->cmd[i]; i++)
				printf("%s\n", cmd->cmd[i]);
		}
		else if (cmd->cmd && (cmd->type == INPUT_DIR || cmd->type == OUTPUT_DIR))
			printf("Output or Input\n");
		else
			printf("Pipe\n");
		write(1, "\n", 1);
		cmd = cmd->next;
	}	
}

void	do_quote_parse(t_node *cmd)
{
	size_t	i;
	size_t	quote;
	size_t	dquote;

	i = -1;
	quote = 0;
	dquote = 0;
	while (cmd->token[++i])
	{
		if (cmd->token[i] == '\"' && !quote % 2)
			dquote++;
		else if (cmd->token[i] == '\'' && !dquote % 2)
			quote++;
		if (quote == 1 && ft_isspace(cmd->token[i]) == TRUE)
			cmd->token[i] = 7;
		else if (dquote == 1 && ft_isspace(cmd->token[i]) == TRUE)
			cmd->token[i] = 7;
	}
}

int	do_parse(t_node *cmd, t_minishell *ms, size_t i)
{
	cmd->token = ft_strfjoin(ft_strjoin(cmd->token, " "), cmd->next->token);
	delete_position(ms->cmd, i + 1);
	i = 0;
	cmd = ms->cmd->head;
	return (i);
}

t_bool	which_parse(t_minishell *ms, t_node *c, size_t *i)
{
	if (check_quote(c->token))
		*i = do_parse(c, ms, *i);
	else if (c->next && c->type == CMD && c->next->type == UNDEFINED)
		*i = do_parse(c, ms, *i);
	else if (c->next && (c->type == 3 || c->type == 2) && c->next->type == -1)
		*i = do_parse(c, ms, *i);
	else
		return (FALSE);
	return (TRUE);
}

void	next_parsing(t_minishell *ms)
{
	t_node	*cmd;
	size_t	i;
	size_t	j;

	i = 0;
	cmd = ms->cmd->head;
	while (cmd && ++i < ms->cmd->size)
	{
		if (which_parse(ms, cmd, &i) == FALSE)
			cmd = cmd->next;
	}
	cmd = ms->cmd->head;
	while (cmd)
	{
		do_quote_parse(cmd);
		j = -1;
		if ((cmd->type == CMD || cmd->type == INPUT_DIR || cmd->type == OUTPUT_DIR) && cmd->token)
			cmd->cmd = ft_split(cmd->token, ' ');
		else
			cmd->cmd = NULL;
		while (cmd->cmd && cmd->cmd[++j])
			cmd->cmd[j] = ft_strtok(cmd->cmd[j], "\7", ' ');
		cmd = cmd->next;
	}
	debug_parsing(ms);
}

size_t ft_sep_len();

void replace_var(char **tab, t_minishell *ms)
{
	
}

void	cmd_parsing(char *buf, t_minishell *ms)
{
	char	*str;
	char	**tab;
	size_t	i;

	str = ft_strtok(buf, " \t\n\r\v\f", 7);
	tab = ft_split(str, 7);
	i = -1;
	while (tab[++i])
	{
		// replace_var(&(tab[i]), ms);
		add_tail(ms->cmd, tab[i]);
		ms->cmd->tail->path = cmd_path(ms);
		ms->cmd->tail->type = which_type(ms->cmd->tail->token, ms->cmd->tail);
	}
	next_parsing(ms);
	free_tab(tab);
}

	// tab = ft_split(str, 7);
	// i = -1;
	// while (tab[++i])
	// {
	// 	add_tail(shell->cmd, ft_split(tab[i], ' '));
	// 	shell->cmd->tail->path = cmd_path(shell);
	// }
	// t_node *actual = shell->cmd->head;
	// while (actual != NULL)
	// {
	// 	printf("%s | %d >> %s\n", actual->token, actual->is_cmd, actual->path);
	// 	actual = actual->next;
	// }

	// 	t_node *actual = ms->cmd->head;
	// while (actual != NULL)
	// {
	// 	printf("===============\nCMD=%s\nTYPE=%d\nPATH=%s\n===============\n\n", actual->token, actual->type, actual->path);
	// 	actual = actual->next;
	// }

	/*
	actuellement le parsing met les dquote et quote dans la même node sauf qu'il ne sont pas sur la même ligne
	- Trouver un moyens de le mettre sur la même ligne 
			->	solution 1 : remplacer les espaces à l'intérieur des quotes pour éviter que le parsing ne les sépare
				puis se baladez dans node->cmd pour remettre les espaces à leur position initiale
				strtok peut être un solutions pour remédiez a cela.
			->	solution 2 : Dans la méthode pour split je modifie pour éviter que le txt entre les quotes ne soit séparer.s
	*/