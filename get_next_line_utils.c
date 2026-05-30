/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkaneko <mkaneko@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/25 16:42:30 by mkaneko           #+#    #+#             */
/*   Updated: 2026/05/30 12:05:23 by mkaneko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlen(const char *str)
{
	size_t	i;

	i = 0;
	while (str[i] != '\0')
	{
		i++;
	}
	return (i);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	s_len;
	char	*sub;
	size_t	cpy_len;
	char	*p;

	if (!s)
		return (NULL);
	s_len = ft_strlen(s);
	if (start >= s_len)
		cpy_len = 0;
	else
	{
		cpy_len = s_len - start;
		if (len < cpy_len)
			cpy_len = len;
	}
	sub = malloc(sizeof(char) * (cpy_len + 1));
	if (!sub)
		return (NULL);
	p = sub;
	s = s + start;
	while (cpy_len--)
		*p++ = *s++;
	*p = '\0';
	return (sub);
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

// char	*ft_strjoin_fast(char *save, size_t save_len, char *buf, size_t buf_len)
// {
// 	char	*res;
// 	char	*p;
// 	char	*s1;

// 	res = malloc(save_len + buf_len + 1);
// 	if (!res)
// 		return (free(save), NULL);
// 	p = res;
// 	s1 = save;
// 	if (s1)
// 	{
// 		while (*s1)
// 			*p++ = *s1++;
// 	}
// 	while (*buf)
// 		*p++ = *buf++;
// 	*p = '\0';
// 	free(save);
// 	return (res);
// }
