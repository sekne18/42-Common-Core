/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jans <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 20:09:24 by jans              #+#    #+#             */
/*   Updated: 2024/10/14 16:09:19 by jsekne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_next_line(int fd)
{
	static char	*line;
	char		*buffer;
	char		*newline;

	buffer = malloc(sizeof(char) * BUFFER_SIZE + 1);
	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, 0, 0) < 0)
	{
		free(line);
		free(buffer);
		line = NULL;
		buffer = NULL;
		return (NULL);
	}
	if (!buffer)
		return (NULL);
	newline = write_to_buffer(fd, buffer, line);
	free(buffer);
	buffer = NULL;
	if (!newline)
		return (NULL);
	line = cut_newline(&newline);
	return (newline);
}

char	*cut_newline(char **newline)
{
	size_t		i;
	char		*line;

	i = 0;
	while ((*newline)[i] != '\n' && (*newline)[i] != '\0')
		i++;
	if ((*newline)[i] == 0 || (*newline)[1] == 0)
		return (NULL);
	line = ft_substr((*newline), i + 1, ft_strlen(*newline) - i);
	if (*line == 0)
	{
		free(line);
		line = NULL;
	}
	(*newline)[i + 1] = 0;
	return (line);
}

char	*write_to_buffer(int fd, char *buffer, char *line)
{
	int		bytes_read;
	char	*tmp;

	bytes_read = 1;
	while (bytes_read > 0)
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read == -1)
		{
			free(line);
			return (NULL);
		}
		else if (bytes_read == 0)
			break;
		buffer[bytes_read] = 0;
		if (!line)
			line = ft_strdup("");
		tmp = line;
		line = ft_strjoin(tmp, buffer);
		free(tmp);
		tmp = NULL;
		if (contains_delimiter(buffer, "\n"))
			break ;
	}
	return (line);
}

int	contains_delimiter(char *line, char *d)
{
	int		i;
	char	*dlm;

	i = -1;
	while (line[++i])
	{
		dlm = d;
		while (*dlm)
		{	
			if (line[i] == *dlm++)
				return (1);
		}
	}
	return (0);
}
