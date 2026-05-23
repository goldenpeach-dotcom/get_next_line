/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkaneko <mkaneko@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/23 00:04:55 by mkaneko           #+#    #+#             */
/*   Updated: 2026/05/23 00:37:35 by mkaneko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H

# include <unistd.h>
# include <stdlib.h>
# include <stddef.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 10
# endif

char	*get_next_line(int fd);
int		find_nl(char *st);
char	*join(char *stash, char *buf);
char	*cut_line(char **stash, int pos);
int		read_join(int fd, char *buf, char **stash);
size_t	ft_strlen_gnl(const char *str);
void	*ft_memcpy_gnl(void *dest, const void *src, size_t n);

#endif
