/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmol <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 16:35:37 by fmol              #+#    #+#             */
/*   Updated: 2024/10/23 11:10:25 by fmol             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <unistd.h>
#include <stdlib.h>

void	reset_buffer(char *buffer)
{
	size_t	i;

	i = 0;
	while (i < BUFFER_SIZE + 1)
	{
		buffer[i] = 0;
		i++;
	}
}

int	has_char(char *buffer, size_t size, char c)
{
	size_t	i;

	i = 0;
	while (i < size)
	{
		if (buffer[i] == c)
			return (i);
		i++;
	}
	return (-1);
}

char	*create_line(char **s_line, int i)
{
	char	*line;
	size_t	len;
	int		j;

	len = ft_strlen(*s_line);
	line = malloc(sizeof(char) * (i + 2));
	j = -1;
	while (++j < i + 1)
		line[j] = (*s_line)[j];
	line[j] = '\0';
	if (i == (int)len - 1)
	{
		free(*s_line);
		*s_line = NULL;
	}
	else
	{
		j = -1;
		while ((*s_line)[++j + i + 1])
			(*s_line)[j] = (*s_line)[j + i + 1];
		(*s_line)[j] = '\0';
	}
	return (line);
}

int	fill_line(int fd, char **s_line, char *buffer)
{
	char		*tmp;
	ssize_t		bytes;
	int			i;

	i = -1;
	bytes = 1;
	while (bytes)
	{
		i = has_char(*s_line, ft_strlen(*s_line), '\n');
		if (i >= 0)
			return (i);
		bytes = read(fd, buffer, BUFFER_SIZE);
		if (bytes == -1)
			return (-1);
		tmp = ft_strjoin(*s_line, buffer);
		reset_buffer(buffer);
		free(*s_line);
		*s_line = tmp;
	}
	i = ft_strlen(*s_line);
	if (bytes != -1 && i > 0)
		return (i - 1);
	return (-1);
}

char	*get_next_line(int fd)
{
	static t_lnode	*s_lines;
	t_lnode			*tmp;
	char			*buffer;
	int				i;

	buffer = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (fd < 0 || read(fd, 0, 0) < 0 || !buffer)
	{
		free(buffer);
		return (NULL);
	}
	tmp = lstfind_fd(s_lines, fd);
	if (!tmp)
		tmp = lstadd_fd(&s_lines, fd);
	if (!tmp || !buffer)
		return (NULL);
	reset_buffer(buffer);
	i = fill_line(fd, &tmp->line, buffer);
	free(buffer);
	if (i >= 0)
		return (create_line(&tmp->line, i));
	lstremove_fd(&s_lines, fd);
	return (NULL);
}
