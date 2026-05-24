/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkaneko <mkaneko@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/22 20:32:12 by mkaneko           #+#    #+#             */
/*   Updated: 2026/05/24 20:43:30 by mkaneko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_next_line(int fd)
{
	static char		*stash;
	static size_t	stash_len;
	char			*buf;
	ssize_t			pos;
	int				has_nl;

	if (fd < 0 || fd >= 1024 || BUFFER_SIZE <= 0)
		return (NULL);
	buf = malloc((size_t)BUFFER_SIZE + 1);
	if (!buf)
		return (NULL);
	pos = 1;
	has_nl = 0;
	while (!has_nl && (pos = read(fd, buf, BUFFER_SIZE)) > 0)
	{
		buf[pos] = '\0';
		if (find_nl(buf) != -1)
			has_nl = 1;
		stash = join_exact_with_len(stash, buf, &stash_len, (size_t)pos); 
		if (!stash)
			return (free(buf), stash_len = 0, NULL);
	}
	free(buf);
	if (pos < 0)
		return (free(stash), stash = NULL, stash_len = 0, NULL);
	if (stash && stash_len > 0 && find_nl(stash) != -1)
		return (cut_line(&stash, find_nl(stash), &stash_len));
	if (stash && *stash != '\0')
		return (buf = stash, stash = NULL, stash_len = 0,buf);
	return (free(stash), stash = NULL, stash_len = 0, NULL);
}