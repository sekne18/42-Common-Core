/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jans <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 23:32:23 by jans              #+#    #+#             */
/*   Updated: 2024/10/22 11:23:05 by jsekne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	main(int argc, char **argv)
{
	char	**map;

	map = NULL;
	if (argc != 2)
		return (0);
	if (parse_map(&map, argv[1]) == 0)
		return (0);
	fdf(map);	
	free_all(map);
	return (0);
}

int	parse_map(char	***map, char *filename)
{
	int		fd;
	char	*line;
	char	*read_line;

	fd = open(filename, O_RDONLY);
	if (fd == -1)
		return (0);
	line = ft_strdup("");
	if (!line)
		return (0);
	while (1)
	{
		read_line = get_next_line(fd);
		if (!read_line)
			break ;
		line = ft_strjoin(line, read_line);
		free(read_line);
	}
	close(fd);
	*map = ft_split(line, '\n');
	free(line);
	return (1);
}
