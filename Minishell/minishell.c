/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stgerard <stgerard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/11 14:47:42 by stgerard          #+#    #+#             */
/*   Updated: 2023/01/26 14:22:25 by stgerard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	shell = (t_minishell *)malloc(sizeof(t_minishell));
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

void	ft_prompt(void)
{
	int				first; // check 1ere ligne, eviter seg fault
	char			*buf;
	t_minishell		*shell;

	// signal(SIGQUIT, sigint_handler);
	// signal(SIGINT, sigint_handler);

	first = 0;
	buf = malloc(sizeof(char));
	shell = ft_init();
	while (buf != NULL)
	{
		if (first == 0)
		{
			first = 1;
			free(buf);
		}
		buf = readline("minishell $>");
		if (buf)
		{
			if (check_input(buf) == 1) // check ascii et ' '
				add_history(buf);
			if (ft_strcmp(buf, "env") == 1)
			{
				ft_env(shell);
			}
			if (ft_strcmp(buf, "pwd") == 1)
			{
				ft_pwd(shell);
			}
			if (ft_strncmp(buf, "echo", 4) == 0)
				ft_echo(buf);
			if (strcmp == )

		}
		// free(buf);
		// ft_parse(buf, shell);
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