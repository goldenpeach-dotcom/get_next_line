/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkaneko <mkaneko@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/25 16:42:30 by mkaneko           #+#    #+#             */
/*   Updated: 2026/05/25 20:26:47 by mkaneko          ###   ########.fr       */
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

char	*ft_strjoin_gnl(char const *s1, char const *s2)
{
	char	*res;
	char	*p;

	if (!s1)
		s1 = "";
	if (!s2)
		return (NULL);
	res = malloc(ft_strlen(s1)+ ft_strlen(s2) + 1);
	if (!res)
		return (NULL);
	p = res;
	while(*s1)
			*p++ = *s1++;	
	while(*s2)
			*p++ = *s2++;
	
	*p = '\0';
	return (res);
}

char	*ft_strdup(const char *s)
{
	size_t	len;
	char	*dest;
	size_t	i;

	len = 0;
	len = ft_strlen(s);
	dest = malloc(len + 1);
	if (!dest)
		return (NULL);
	i = 0;
	while (s[i])
	{
		dest[i] = s[i];
		i++;
	}
	dest[len] = '\0';
	return (dest);
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
