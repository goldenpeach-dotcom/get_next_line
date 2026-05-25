/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkaneko <mkaneko@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/22 20:29:38 by mkaneko           #+#    #+#             */
/*   Updated: 2026/05/25 12:37:35 by mkaneko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	find_nl(char *st)
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

char	*join_exact_with_len(char *stash, char *buf, size_t	*s_len, size_t pos)
{
	char	*new;
	size_t	i;
	size_t	total;

	if (!stash)
		*s_len = 0;
	total = *s_len + pos;
	new = malloc(total + 1);
	if (!new)
		return (free(stash), NULL);
	i = 0;
	while (i < *s_len)
	{
		new[i] = stash[i];
		i++;
	}
	while (i < total)
	{
		new[i] = buf[i - *s_len];
		i++;
	}		
	return (new[i] = '\0', *s_len = i, free(stash), new);
}

char	*cut_line(char	**stash, int pos, size_t *s_len)
{
	char	*line;
	char	*new_stash;
	size_t		i;
	size_t		remain;

	line = malloc(pos + 2);
	if (!line)
		return (free(*stash), *stash = NULL, *s_len = 0, NULL);
	i = 0;
	while (i <= (size_t)pos)
	{
		line[i] = (*stash)[i];
		i++;
	}
	line[i] = '\0';
	remain = *s_len - i;
	// printf("pos=%d s_len=%zu\n", pos, *s_len);
	// printf("stash=%s\n", *stash);
	// printf("i=%d\n", i);
	if (remain == 0)
		return (free(*stash), *stash = NULL, *s_len = 0, line);
	new_stash = malloc(remain + 1);
	if (!new_stash)
		return (free(line), free(*stash), *stash = NULL, *s_len = 0, NULL);
	while (i < remain)
	{
		new_stash[i] = (*stash)[(size_t)pos + 1 + i];
		i++;
	}
	new_stash[i] = '\0';
	return (*s_len = remain, free(*stash), *stash = new_stash, line);
}

char	*append_char(char *stash, char c, size_t *s_len)
{
	char	*new_str;
	size_t	i;

	new_str = malloc(*s_len + 2);
	if (!new_str)
		return (free(stash), NULL);
	i = 0;
	if (stash)
	{
		while (i < *s_len)
		{
			new_str[i] = stash[i];
			i++;
		}
	}
	new_str[i] = c;
	new_str[i + 1] = '\0';
	*s_len += 1;
	free(stash);
	return (new_str);
}
