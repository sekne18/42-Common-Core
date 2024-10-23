/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jans <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 20:53:12 by jans              #+#    #+#             */
/*   Updated: 2024/10/23 16:33:43 by jsekne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_point	***get_points_array(char **map)
{
	t_point	***points;
	int		i;
	int		len_y;

	len_y = 0;
	i = 0;
	if (!map)
		return (NULL);
	while (map[len_y])
		len_y++;
	points = malloc((len_y + 1) * sizeof(t_point **));
	if (!points)
		return (NULL);
	i = -1;
	while (map[++i])
		points[i] = get_cols(map[i], i);
	points[i] = 0;
	return (points);
}

t_point	**get_cols(char *line, int y)
{
	char	**formatted;
	int		x;
	t_point	**point_arr;
	int		len_x;

	len_x = 0;
	x = -1;
	formatted = ft_split(line, ' ');
	if (!formatted)
		return (NULL);
	while (formatted[len_x])
		len_x++;
	point_arr = malloc((len_x + 1) * sizeof(t_point *));
	if (!point_arr)
		return (NULL);
	while (formatted[++x])
		point_arr[x] = ft_new_point(x, y, ft_atoi(formatted[x]), ft_new_info(len_x, y));
	//point_arr[x] = 0;
	free_all(formatted);
	return (point_arr);
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
