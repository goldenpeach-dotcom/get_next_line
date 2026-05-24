/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkaneko <mkaneko@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/23 00:04:55 by mkaneko           #+#    #+#             */
/*   Updated: 2026/05/24 20:28:05 by mkaneko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <unistd.h>
# include <stdlib.h>
# include <stddef.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 10
# endif

char	*get_next_line(int fd);
int		find_nl(char *st);
char	*join_exact_with_len(char *stash, char *buf, size_t	*s_len, size_t pos);
char	*cut_line(char	**stash, int pos, size_t *s_len);
char	*append_char(char *stash, char c, size_t *s_len);



#endif
