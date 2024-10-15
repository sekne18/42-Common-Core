/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jans <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 20:10:03 by jans              #+#    #+#             */
/*   Updated: 2024/10/14 08:17:14 by jsekne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 10
# endif
# include <stdlib.h>
# include <unistd.h>

size_t	ft_strlen(const char *s);
int		contains_delimiter(char *line, char *d);
int		str_length(const char *s1, const char *s2);
char	*ft_substr(char const *s, unsigned int start, size_t len);
char	*write_to_buffer(int fd, char *buffer, char *line);
char	*ft_strjoin(char *s1, char const *s2);
char	*cut_newline(char **newline);
char	*get_next_line(int fd);
char	*ft_strdup(const char *s);
#endif
