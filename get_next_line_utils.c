/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkaneko <mkaneko@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/22 20:29:38 by mkaneko           #+#    #+#             */
/*   Updated: 2026/05/23 19:32:39 by mkaneko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*join(char	*stash, char	*buf)
{
	char	*new;
	size_t	s_len;
	size_t	b_len;

	s_len = 0;
	b_len = 0;
	while (stash && stash[s_len])
		s_len++;
	while (buf && buf[b_len])
		b_len++;
	new = malloc(s_len + b_len + 1);
	if (!new)
		return (free(stash), NULL);
	new[s_len + b_len] = '\0';
	while(b_len > 0)
	{
		b_len--;
		new[s_len + b_len] = buf[b_len];
	}		
	while(s_len > 0)
	{
		s_len--;
		new[s_len] = stash[s_len];
	}
	free(stash);
	return (new);
}

static char	*copy_remains(char *old_stash, int pos, int total_len, char *line)
{
	char	*new_stash;
	int		i;

	new_stash = malloc(total_len - pos);
	if (!new_stash)
	{
		free(line);
		return (NULL);
	}
	i = 0;
	while (old_stash[pos + 1 + i])
	{
		new_stash[i] = old_stash[pos + 1 + i];
		i++;
	}
	new_stash[i] = '\0';
	free(old_stash);
	return (new_stash);
}

char	*cut_line(char **stash, int pos)
{
	char	*line;
	int		i;

	line = malloc(pos + 2);
	if (!line)
		return (NULL);
	i = -1;
	while (++i <= pos)
		line[i] = (*stash)[i];
	line[i] = '\0';
	while ((*stash)[i])
		i++;
	if ((*stash)[pos + 1] == '\0')
	{
		free(*stash);
		*stash = NULL;
		return (line);
	}
	*stash = copy_remains(*stash, pos, i, line);
	if (!*stash)
		return (NULL);
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

// int	read_join(int fd, char *buf, char **stash)
// {
// 	ssize_t	n;

// 	n = read(fd, buf, BUFFER_SIZE);
// 	if (n <= 0)
// 		return (0);
// 	buf[n] = '\0';
// 	*stash = join(*stash, buf);
// 	if (!stash)
// 		return (0);
// 	return (1);
// }
