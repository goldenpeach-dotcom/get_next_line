/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkaneko <mkaneko@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/25 16:33:56 by mkaneko           #+#    #+#             */
/*   Updated: 2026/05/26 18:47:25 by mkaneko          ###   ########.fr       */
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
	if (!save || !ft_strchr(save , '\n'))
		save = read_and_join(fd, save, &save_len,&al_size);
	if (!save)
		return (NULL);
	line = cut_line_and_update_save(&save, &save_len, &al_size);
	return (line);
}

static int	append_buf(char	*save, char *buf, size_t *save_len, size_t	read_bytes)
{
	size_t	i;
	int		has_nl;
	
	i = 0;
	has_nl = 0;
	
	while(i < (size_t)read_bytes)
	{
		save[*save_len] = buf[i];
		if (buf[i] == '\n')
			has_nl = 1;
		*save_len = *save_len + 1;
		i++;
	}
	return (has_nl);
}

char	*read_and_join(int fd, char *save, size_t *save_len, size_t *al_size)
{
	char	*buf;
	ssize_t	read_bytes;
	
	buf = malloc(sizeof(char) * ((size_t)BUFFER_SIZE + 1));
	if (!buf)
		return (free(save), NULL);
	while (1)
	{
		read_bytes = read(fd, buf, BUFFER_SIZE);
		if (read_bytes <= 0)
			break ;
		if (*save_len + read_bytes >= *al_size)
		{
			save = extend_save(save, *save_len, *save_len + read_bytes + 1, al_size);
			if (!save)
				return (free(buf), NULL);
		}	
		if (append_buf(save, buf, save_len, (size_t)read_bytes))
			break ;
	}			
	if (save && read_bytes >= 0)
		save[*save_len] = '\0';
	if (read_bytes == -1)
		return(free(buf), free(save),NULL);
	return (free(buf),save);
}


char	*cut_line_and_update_save(char **save_ptr, size_t *save_len, size_t *al_size)
{
	char	*line;
	char	*next_start;
	char	*old_save;
	size_t	line_len;
	size_t	remain_len;

	old_save = *save_ptr;
	if (!old_save || *old_save == '\0')
		return (free(*save_ptr), *save_ptr = NULL, *al_size = 0 ,NULL);
	next_start = ft_strchr(old_save, '\n');
	if (!next_start)
	{
		line = ft_substr(old_save, 0, *save_len);
		return (free(old_save), *save_ptr = NULL, *save_len = 0, *al_size = 0, line);
	}
	line_len = (next_start - old_save) + 1;
	line = ft_substr(old_save, 0, line_len);
	remain_len = *save_len - line_len;
	*save_ptr = NULL;
	*al_size = 0;
	if (remain_len > 0 && (*al_size = remain_len + 1))
		*save_ptr = ft_substr(old_save, line_len, remain_len);
	*save_len = remain_len;
	return (free(old_save), line);
}

char	*extend_save(char *save, size_t current_len, size_t needed_len, size_t *al_size)
{
	char	*new_save;
	size_t	new_size;
	size_t	i;

	if (needed_len < *al_size)
		return (save);
	new_size = *al_size * 2;
	if (new_size < needed_len)
		new_size = needed_len + BUFFER_SIZE + 1024; // 初期状態や足りない場合は多めに確保
	
	new_save = malloc(new_size);
	if (!new_save)
		return (free(save), NULL);
	i = 0;
	if (save)
	{
		while (i < current_len)
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
	// read_bytes = 1;
	// while (read_bytes > 0)
	// {
	// 	read_bytes = read(fd, buf, BUFFER_SIZE);
	// 	if (read_bytes == -1)
	// 		return (free(buf), free(save), NULL);
	// 	if (read_bytes == 0)
	// 		break ;
	// 	buf[read_bytes] = '\0';
	// 	save = ft_strjoin_fast(save, *save_len, buf, read_bytes);
	// 	if (!save)
	// 		return (free(buf), NULL);
	// 	*save_len = *save_len + read_bytes;
	// 	if (BUFFER_SIZE == 1)
	// 	{
	// 		if (buf[0] == '\n')
	// 			break ;
	// 	}
	// 	else if (ft_strchr(buf, '\n'))
	// 		break ;
	// }
	// free(buf)