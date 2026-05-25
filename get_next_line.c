/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkaneko <mkaneko@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/25 16:33:56 by mkaneko           #+#    #+#             */
/*   Updated: 2026/05/25 20:31:06 by mkaneko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_next_line(int fd)
{
	static char	*save;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	save = read_and_join(fd, save);
	if (!save)
		return (NULL);
	line = cut_line_and_update_save(&save);
	return (line);
}
// ステップ1: 改行が見つかるまでファイルから読み込み、saveに蓄積する
char	*read_and_join(int fd, char *save)
{
	char	*buf;
	char	*temp;
	ssize_t	read_bytes;

	buf = malloc(sizeof(char) * ((size_t)BUFFER_SIZE + 1));
	if (!buf)
		return (free(save), NULL);
	read_bytes = 1;
	// saveの中に改行がない、かつファイルがまだ読める間ループ
	while (read_bytes > 0)
	{
		read_bytes = read(fd, buf, BUFFER_SIZE);
		if (read_bytes == -1)
			return(free(buf), free(save), NULL);
		buf[read_bytes] = '\0';
		temp = ft_strjoin_gnl(save, buf); // 独自のstrjoin（saveがNULLでも動くように工夫すると楽）
		free(save);
		save = temp;
		if (ft_strchr(buf,'\n'))
			break;
	}
	free(buf);
	return (save);
}

// ステップ2 & 3: saveから1行を切り出し、残りを次のために残す
char	*cut_line_and_update_save(char **save_ptr)
{
	char	*line;
	char	*next_start;
	char	*old_save;

	old_save = *save_ptr;
	if (!old_save || *old_save == '\0')
		return (free(*save_ptr), *save_ptr = NULL, NULL);
	// 改行の位置を探す
	next_start = ft_strchr(old_save, '\n');
	if (next_start)
	{
		// 改行までを切り出す（改行そのものも含める）
		line = ft_substr(old_save, 0, next_start - old_save + 1);
		// 残りの文字列を新しい静的変数にする
		*save_ptr = ft_strdup(next_start + 1);
	}
	else
	{
		// 改行がなければ、残っているすべてが最後の1行
		line = ft_strdup(old_save);
		*save_ptr = NULL;
	}
	free(old_save);
	return (line);
}

char	*ft_strchr(const char *s, int c)
{
	size_t	i;

	i = 0;
	while (s[i] != '\0')
	{
		if (s[i] == (char)c)
			return ((char *)s + i);
		i++;
	}
	if ((char)c == '\0')
		return ((char *)s + i);
	return (NULL);
}
char	*ft_strjoin_fast(char *save, size_t save_len, char *buf, size_t buf_len)
{
	char	*res;
	char	*p;
	char	*s1;

	res = malloc(save_len + buf_len + 1);
	if (!res)
		return (free(save), NULL);
	p = res;
	s1 = save;
	// s1 (save) のコピー
	if (s1)
	{
		while (*s1)
			*p++ = *s1++;
	}
	// buf のコピー
	while (*buf)
		*p++ = *buf++;
	*p = '\0';
	free(save); // 古い save はここで解放するとメイン側がスッキリします
	return (res);
}
