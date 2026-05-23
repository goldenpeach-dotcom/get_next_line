/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkaneko <mkaneko@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/22 20:32:12 by mkaneko           #+#    #+#             */
/*   Updated: 2026/05/23 19:48:18 by mkaneko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_next_line(int fd)
{
	static char		*stash;
	char			*buf;
	ssize_t			pos;
	char			*line;

	if (fd < 0 || fd >= 1024 || BUFFER_SIZE <= 0)
		return (NULL);
	buf = malloc((size_t)BUFFER_SIZE + 1);
	if (!buf)
		return (NULL);
	while (find_nl(stash) == -1 && (pos = read(fd, buf, BUFFER_SIZE))> 0)
	{
		buf[pos] = '\0';
		stash = join(stash, buf);
	}
	free(buf);
	if (pos < 0)
		return (free(stash), stash = NULL, NULL);
	if (find_nl(stash) != -1)
		return (cut_line(&stash, find_nl(stash)));
	if  (stash && *stash)
		return (line = stash, stash = NULL, line);
	return (line = stash, stash = NULL, NULL);
}
