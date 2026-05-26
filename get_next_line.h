/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkaneko <mkaneko@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/23 00:04:55 by mkaneko           #+#    #+#             */
/*   Updated: 2026/05/26 17:17:10 by mkaneko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <unistd.h>
# include <stdlib.h>
# include <stddef.h>
# include <stdio.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 10
# endif

char	*get_next_line(int fd);
char	*read_and_join(int fd, char *save, size_t *save_len, size_t *al_size);
char	*cut_line_and_update_save(char **save_ptr, size_t *save_len, size_t *al_size);
char	*ft_substr(char const *s, unsigned int start, size_t len);
char	*ft_strchr(const char *s, int c);
char	*ft_strjoin_fast(char *save, size_t save_len, char *buf, size_t buf_len);
size_t	ft_strlen(const char *str);
char	*extend_save(char *save, size_t current_len, size_t needed_len, size_t *al_size);

#endif
