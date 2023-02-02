/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: misimon <misimon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/11 14:47:42 by stgerard          #+#    #+#             */
/*   Updated: 2023/02/02 16:04:37 by misimon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	ft_free_shell(t_minishell *shell)
{
	close(shell->fd_in);
	close(shell->fd_out);
	// /!\ free un tableau

	free(shell->path);
	free(shell->env);
	free(shell);
}

t_minishell	*ft_init(void)
{
	t_minishell	*shell;
	int			i;
	extern char	**environ;

	i = 0;
	shell = malloc(sizeof(t_minishell));
	shell->cmd = create_list();
	if (!shell || !shell->cmd)
		return (NULL);
	while (environ[i])
		i++;
	shell->env = (char **)malloc(sizeof(char *) * i + 1);
	shell->env[i] = 0;
	i = 0;
	while (environ[i])
	{
		shell->env[i] = ft_strdup(environ[i]);
		i++;
	}
	shell->path = ft_split(getenv("PATH"), ':');
	shell->fd_in = 0;
	shell->fd_out = 0;
	return (shell);
}

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

// void	do_cmd(t_minishell *shell, char *buf)
// {
// 	t_node	*actual_cmd;

// 	actual_cmd = shell->cmd->head;
// 	while (actual_cmd)
// 	{
		// if (check_input(buf) == 1)
		// 	add_history(buf);
		// if (ft_strcmp(actual_cmd->cmd[0], "env") == 0)
		// 	ft_env(shell);
		// else if (ft_strcmp(actual_cmd->cmd[0], "pwd") == 0)
		// 	ft_pwd(actual_cmd);
		// else if (ft_strcmp(actual_cmd->cmd[0], "echo") == 0)
		// 	ft_echo(actual_cmd);
		// else if (ft_strcmp(actual_cmd->cmd[0], "export") == 0)
		// 	ft_export(buf);
		// else
		// 	printf("stop\n");
// 		actual_cmd = actual_cmd->next;
// 	}
// }

void	ft_prompt(void)
{
	char			*buf;
	t_minishell		*shell;

	signal(SIGINT, sigint_handler);
	signal(SIGQUIT, sigint_handler);
	signal(SIGTERM, sigint_handler);
	// sigint_handler(1);

	buf = NULL;
	shell = ft_init();
	while (1)
	{
		// sigint_handler(2);
		if (buf)
			free(buf);
		buf = readline("Minishell$> ");
		cmd_parsing(buf, shell);
		// do_cmd(shell, buf);
		delete_all_list(shell->cmd);
		// free(buf);
		// builtins(buf);

	}
	// ft_free_shell(shell);
}

int	main(int ac, char **av)
{
	// int			i;
	(void)ac;
	(void)av;
	// t_minishell		*shell;

	// i = -1;
	// ft_init(&shell, envp);
	// shell->path = ft_split(getenv("PATH"), ':');
	// while (path[++i])
	// 	path[i] = ft_strjoin(path[i], "/");
	ft_prompt();
	
	// ft_free_shell(shell);
}

/*

char *getcwd(char *buf, size_t size);  copie le chemin d'accès absolu du répertoire de travail courant dans la chaîne pointée par buf, qui est de longueur size
int unlink(const char *pathname); unlink() détruit un nom dans le système de fichiers. Si ce nom était le dernier lien sur un fichier, et si aucun processus n'a ouvert ce fichier, ce dernier est effacé
pid_t fork(void);
int execve(const char *fichier, char *const argv[],
int dup(int oldfd);
int dup2(int oldfd, int newfd)

char * getcwd( char *buffer, size_t size ); // pour le pwd

ft_split(PATH, ':');

*/
