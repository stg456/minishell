/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: misimon <misimon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/09 15:15:34 by stgerard          #+#    #+#             */
/*   Updated: 2023/03/02 16:41:31 by misimon          ###   ########.fr       */
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
	else if ((cmd->path)
		|| !ft_strcmp(str, "export") || !ft_strcmp(str, "unset")
		|| !ft_strcmp(str, "exit"))
		return (CMD);
	else if (cmd->token[0] == 6)
		return (QUOTE);
	else if (cmd->token[0] == 5)
		return (DQUOTE);
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

int	do_parse(t_node *cmd, t_minishell *ms, size_t i)
{
	cmd->token = ft_strtok(cmd->token, "\6\5", '\7');
	cmd->token = ft_strfjoin(ft_strjoin(cmd->token, " "), cmd->next->token);
	delete_position(ms->cmd, i + 1);
	i = 0;
	cmd = ms->cmd->head;
	return (i);
}

t_bool	which_parse(t_minishell *ms, t_node *c, size_t *i)
{
	if (c->next && c->type == CMD && (c->next->type == UNDEFINED
			|| c->next->type == DQUOTE || c->next->type == QUOTE))
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
		j = -1;
		if ((cmd->type == CMD || cmd->type == INPUT_DIR || cmd->type == OUTPUT_DIR) && cmd->token)
			cmd->cmd = ft_split(cmd->token, ' ');
		else
			cmd->cmd = NULL;
		while (cmd->cmd && cmd->cmd[++j])
			cmd->cmd[j] = ft_strtok(cmd->cmd[j], "\4", ' ');
		cmd = cmd->next;
	}
	debug_parsing(ms);
}

char	*replace_quote_space(char *buf)
{
	size_t	quote;
	size_t	dquote;
	size_t	i;
	char	*new_buf;

	new_buf = ft_strdup(buf);
	if (!new_buf)
		return (0);
	free(buf);
	i = -1;
	quote = 0;
	dquote = 0;
	while (new_buf[++i])
	{
		if (ft_isspace(new_buf[i]) && (dquote % 2 || quote % 2))
			new_buf[i] = 4;
		if (new_buf[i] == '\'' && !(dquote % 2))
		{
			new_buf[i] = 6;
			quote++;
		}
		else if (new_buf[i] == '\"' && !(quote % 2))
		{
			new_buf[i] = 5;
			dquote++;
		}
	}
	return (new_buf);
}

size_t	var_len_start(char *str)
{
	size_t	i;

	i = 0;
	while (str[i] != '$' && str[i])
		i++;
	return (i);
}	

size_t	name_len(char *str)
{
	size_t	i;

	i = var_len_start(str) + 1;
	if (str[i] == '?')
		return (1);
	while ((ft_isalnum(str[i])) && str[i])
		++i;
	return (i - var_len_start(str) - 1);
}

char	*ft_strndup(char *s1, size_t n, size_t start)
{
	char	*chr;
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	if (!n || !s1)
		return (NULL);
	chr = malloc(sizeof(char) * (n + 1));
	if (!chr)
		return (NULL);
	while (s1[i] && j < n)
	{
		if (i >= start && s1[i])
		{
			chr[j] = s1[i];
			j++;
		}
		i++;
	}
	chr[j] = '\0';
	return (chr);
}

char	*get_env_var(char *name, t_minishell *ms)
{
	char	**env;
	char	*value;
	size_t	len;

	env = ms->env;
	if (!name)
		return (NULL);
	len = ft_strlen(name);
	printf("%d\n", ft_strcmp(name, "?"));
	if (ft_strcmp(name, "?") == 0)
	{
		value = ft_itoa(ms->status);
		printf("%s\n", value);
		return (value);
	}
	while (*env)
	{
		if (!ft_strncmp(*env, name, len) && (*env)[len] == '=')
		{
			value = ft_strdup(*env + len + 1);
			free(name);
			if (!value)
				return (NULL);
			return (value);
		}
		env++;
	}
	return (NULL);
}

char	*do_var_replacement(char *str, t_minishell *ms)
{
	size_t	l[2];
	char	*str_end;
	char	*var_name;
	char	*str_start;

	if (!str)
		return (NULL);
	l[0] = var_len_start(str);
	l[1] = name_len(str);
	str_start = ft_strndup(str, l[0], 0);
	var_name = ft_strndup(str, l[1], l[0] + 1);
	str_end = ft_strdup(str + l[1] + l[0] + 1);
	var_name = get_env_var(var_name, ms);
	free(str);
	if (str_start && var_name && str_end)
		str = ft_strfjoin(ft_strfjoin(str_start, var_name), str_end);
	else if (str_start && var_name)
		str = ft_strfjoin(str_start, var_name);
	else if (var_name && str_end)
		str = ft_strfjoin(var_name, str_end);
	else if (str_start && str_end)
		str = ft_strfjoin(str_start, str_end);
	else if (str_start)
		str = ft_strdup(str_start);
	else if (var_name)
		str = ft_strdup(var_name);
	else if (str_end)
		str = ft_strdup(str_end);
	else
		str = NULL;
	return (str);
}

void	check_token_var(t_node *node, t_minishell *ms)
{
	size_t	i;

	if (!node || (node->type != UNDEFINED && node->type != DQUOTE))
		return ;
	else if (node && node->token)
	{
		i = -1;
		while (node->token[++i])
		{
			if (node->token[i] == '$')
			{
				node->token = do_var_replacement(node->token, ms);
				i = -1;
			}
		}
	}
}

void	cmd_parsing(char *buf, t_minishell *ms)
{
	char	*temp;
	char	**token_tab;
	size_t	i;

	(void)ms;
	temp = replace_quote_space(ft_strdup(buf));
	if (!temp)
		return ;
	temp = ft_strtok(temp, " \t\n\r\v\f", 7);
	token_tab = ft_split(temp, 7);
	free(temp);
	i = -1;
	while (token_tab[++i])
	{
		add_tail(ms->cmd, token_tab[i]);
		ms->cmd->tail->path = cmd_path(ms);
		ms->cmd->tail->type = which_type(ms->cmd->tail->token, ms->cmd->tail);
		check_token_var(ms->cmd->tail, ms);
	}
	next_parsing(ms);
	free_tab(token_tab);
}

// void	cmd_parsing(char *buf, t_minishell *ms)
// {
// 	char	*str;
// 	char	**tab;
// 	size_t	i;

// 	str = ft_strtok(buf, " \t\n\r\v\f", 7);
// 	tab = ft_split(str, 7);
// 	i = -1;
// 	while (tab[++i])
// 	{
// 		// replace_var(&(tab[i]), ms);
// 		add_tail(ms->cmd, tab[i]);
// 		ms->cmd->tail->path = cmd_path(ms);
// 		ms->cmd->tail->type = which_type(ms->cmd->tail->token, ms->cmd->tail);
// 	}
// 	next_parsing(ms);
// 	free_tab(tab);
// }

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
	// 	actual = actual->next;
	// }
