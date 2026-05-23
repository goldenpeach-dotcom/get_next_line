/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkaneko <mkaneko@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/22 20:29:38 by mkaneko           #+#    #+#             */
/*   Updated: 2026/05/23 14:26:18 by mkaneko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"


char	*join(char	*stash, char	*buf)
{
	char	*new;
	size_t	s_len;
	size_t	b_len;

	s_len = 0;
	if (stash)
		s_len = ft_strlen_gnl(stash);
	b_len = ft_strlen_gnl(buf);
	new = malloc(s_len + b_len + 1);
	if (!new)
		return (free(stash), NULL);
	if (stash)
	{
		ft_memcpy_gnl(new, stash, s_len);
		free(stash);
	}
	ft_memcpy_gnl(new + s_len, buf, b_len);
	new[s_len + b_len] = '\0';
	return (new);
}

char	*cut_line(char	**stash, int pos)
{
	char	*line;
	char	*new_stash;
	size_t	len;

	line = malloc(pos + 2);
	if (!line)
		return (NULL);
	ft_memcpy_gnl(line, *stash, pos + 1);
	line[pos + 1] = '\0';
	len = ft_strlen_gnl(*stash + pos + 1);
	if (len == 0)
	{
		free(*stash);
		*stash = NULL;
		return (line);
	}
	new_stash = malloc(len + 1);
	if (!new_stash)
		return (free(line), NULL);
	ft_memcpy_gnl(new_stash, *stash + pos + 1, len);
	new_stash[len] = '\0';
	free(*stash);
	*stash = new_stash;
	return (line);
}

int	find_nl(char	*st)
{
	int	i;

	i = 0;
	if (!st)
		return (-1);
	while (st[i])
	{
		if (st[i] == '\n')
			return (i);
		i++;
	}
	return (-1);
}

int	read_join(int fd, char *buf, char **stash)
{
	ssize_t	n;

	n = read(fd, buf, BUFFER_SIZE);
	if (n <= 0)
		return (0);
	buf[n] = '\0';
	*stash = join(*stash, buf);
	return (1);
}

size_t	ft_strlen_gnl(const char *str)
{
	size_t	i;

	i = 0;
	while (str[i] != '\0')
	{
		i++;
	}
	return (i);
}

void	*ft_memcpy_gnl(void *dest, const void *src, size_t n)
{
	unsigned char		*d;
	const unsigned char	*s;
	size_t				i;

	if (!dest && !src)
		return (NULL);
	d = (unsigned char *)dest;
	s = (const unsigned char *)src;
	i = 0;
	while (n > i)
	{
		d[i] = s[i];
		i++;
	}
	return (dest);
}
