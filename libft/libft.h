/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: misimon <misimon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/27 13:57:30 by misimon           #+#    #+#             */
/*   Updated: 2023/01/29 16:07:12 by misimon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 60
# endif

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <stdarg.h>
# include <fcntl.h>
# include <limits.h>
# include "include/libft_struct.h"

t_bool	ft_isalpha(int c);
t_bool	ft_isdigit(int c);
t_bool	ft_isalnum(int c);
t_bool	ft_isascii(int c);
t_bool	ft_isprint(int c);
t_bool	ft_issign(char c);
t_bool	ft_isspace(int c);
int		ft_toupper(int c);
int		ft_tolower(int c);
int		ft_error(void);
int		ft_atoi(const char *str);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
int		ft_memcmp(const void *s1, const void *s2, size_t n);
int		ft_strcmp(const char *s1, const char *s2);
int		free_tab(char **tab);
size_t	ft_strlen(const char *s);
size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize);
size_t	ft_strlcat(char *dst, const char *src, size_t dstsize);
void	ft_putendl_fd(char *s, int fd);
void	ft_putnbr_fd(int n, int fd);
void	ft_putchar_fd(char c, int fd);
void	ft_putstr_fd(char *s, int fd);
void	*ft_memccpy(void *dest, const void *src, int c, size_t n);
void	*ft_memset(void *b, int c, size_t len);
void	ft_bzero(void *s, size_t n);
void	*ft_memcpy(void *dst, const void *src, size_t n);
void	*ft_memmove(void *dst, const void *src, size_t len);
void	*ft_memchr(const void *s, int c, size_t n);
void	*ft_calloc(size_t nmemb, size_t size);
void	ft_striteri(char *s, void (*f)(unsigned int, char*));
char	*ft_strtrim(char const *s1, char const *set);
char	*ft_itoa(int n);
char	*ft_strchr(const char *s, int c);
char	*ft_strrchr(const char *s, int c);
char	*ft_strnstr(const char *haystack, const char *needle, size_t len);
char	*ft_strdup(const char *s1);
char	*ft_substr(char const *s, unsigned int start, size_t len);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_strmapi(char const *s, char (*f)(unsigned int, char));
char	**ft_split(char const *s, char c);

int		ft_p_ptr(unsigned long ptr, int p_len);
int		ft_p_hex(unsigned int hexn, int p_len, const char c);
int		ft_p_char(int c);
int		ft_p_str(char *str);
int		ft_p_unsigned(unsigned int n, int p_len);
int		ft_p_putnbr(int n, int p_len);
int		ft_ptrlen(unsigned long ptr);
char	*ft_uitoa(unsigned int n);
int		ft_printf(const char *str, ...);

char	*get_next_line(int fd);
char	*ft_strfjoin(char *s1, char *s2);

#endif

/*
static void	*xmalloc(size_t size)
{
	static int	mal = 1;
	static int	i = 0;

	++i;
	if (i == mal)
	{
		printf("malloc %d crashed\n", i);
		return (NULL);
	}
	return (malloc(size));
}

#define malloc(x) xmalloc(x)*/