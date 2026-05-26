/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkaneko <mkaneko@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/25 16:33:56 by mkaneko           #+#    #+#             */
/*   Updated: 2026/05/27 00:08:54 by mkaneko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_next_line(int fd)
{
	static char		*save;
	char			*line;
	static size_t	al_size;
	size_t			save_len;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	if (save)
		save_len = ft_strlen(save);
	else
	{
		save_len = 0;
		al_size = 0;
	}
	if (!save || !ft_strchr(save, '\n'))
		save = read_and_join(fd, save, &save_len, &al_size);
	if (!save)
		return (NULL);
	line = cut_line_update_save(&save, &save_len, &al_size);
	return (line);
}

static int	append_buf(char	*save, char *buf, size_t *s_len, size_t	r_bytes)
{
	size_t	i;
	int		has_nl;

	i = 0;
	has_nl = 0;
	while (i < (size_t)r_bytes)
	{
		save[*s_len] = buf[i];
		if (buf[i] == '\n')
			has_nl = 1;
		*s_len = *s_len + 1;
		i++;
	}
	return (has_nl);
}

char	*read_and_join(int fd, char *save, size_t *s_len, size_t *al_size)
{
	char	*buf;
	ssize_t	r_bytes;

	buf = malloc(sizeof(char) * ((size_t)BUFFER_SIZE + 1));
	if (!buf)
		return (free(save), NULL);
	while (1)
	{
		r_bytes = read(fd, buf, BUFFER_SIZE);
		if (r_bytes <= 0)
			break ;
		if (*s_len + r_bytes >= *al_size)
		{
			save = extend_save(save, *s_len, *s_len + r_bytes + 1, al_size);
			if (!save)
				return (free(buf), NULL);
		}	
		if (append_buf(save, buf, s_len, (size_t)r_bytes))
			break ;
	}			
	if (save && r_bytes >= 0)
		save[*s_len] = '\0';
	if (r_bytes == -1)
		return (free(buf), free(save), NULL);
	return (free(buf), save);
}

char	*cut_line_update_save(char **save_ptr, size_t *s_len, size_t *al_size)
{
	char	*line;
	char	*next_start;
	char	*o_save;
	size_t	line_len;
	size_t	remain_len;

	o_save = *save_ptr;
	if (!o_save || *o_save == '\0')
		return (free(*save_ptr), *save_ptr = NULL, *al_size = 0, NULL);
	next_start = ft_strchr(o_save, '\n');
	if (!next_start)
	{
		line = ft_substr(o_save, 0, *s_len);
		return (free(o_save), *save_ptr = NULL, *s_len = 0, *al_size = 0, line);
	}
	line_len = (next_start - o_save) + 1;
	line = ft_substr(o_save, 0, line_len);
	remain_len = *s_len - line_len;
	*save_ptr = NULL;
	*al_size = 0;
	if (remain_len > 0 && (*al_size == remain_len + 1))
		*save_ptr = ft_substr(o_save, line_len, remain_len);
	*s_len = remain_len;
	return (free(o_save), line);
}

char	*extend_save(char *save, size_t c_len, size_t n_len, size_t *al_size)
{
	char	*new_save;
	size_t	new_size;
	size_t	i;

	if (n_len < *al_size)
		return (save);
	new_size = *al_size * 2;
	if (new_size < n_len)
		new_size = n_len + BUFFER_SIZE + 1024;
	new_save = malloc(new_size);
	if (!new_save)
		return (free(save), NULL);
	i = 0;
	if (save)
	{
		while (i < c_len)
		{
			new_save[i] = save[i];
			i++;
		}
		free(save);
	}
	*al_size = new_size;
	return (new_save);
}

// s1 (save) のコピー
// ステップ1: 改行が見つかるまでファイルから読み込み、saveに蓄積する
// ステップ2 & 3: saveから1行を切り出し、残りを次のために残す
