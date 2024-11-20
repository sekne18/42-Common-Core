/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jans <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 20:53:12 by jans              #+#    #+#             */
/*   Updated: 2024/11/20 15:55:21 by jsekne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_point	***get_points_array(char **map, t_vars *vars)
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
	{
		points[i] = get_cols(map[i], i, len_y);
		if (!points[i])
			free_points(points);
	}
	points[i] = 0;
	set_z_limits(points, vars);
	return (points);
}

t_point	**get_cols(char *line, int y, int len_y)
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
		point_arr[x] = ft_new_point(x, y, ft_atoi(formatted[x]),
				ft_new_info(len_x, len_y));
	free_all(formatted);
	return (point_arr);
}

int	parse_map(char ***map, char *filename)
{
	int		fd;
	char	*line;

	fd = open(filename, O_RDONLY);
	if (fd == -1)
		return (0);
	line = ft_strdup("");
	if (!line)
		return (0);
	get_lines(fd, &line);
	close(fd);
	if (ft_strlen(line) == 0)
	{
		free(line);
		return (0);
	}
	*map = ft_split(line, '\n');
	free(line);
	return (1);
}

void	get_lines(int fd, char **line)
{
	char	*tmp;
	char	*read_line;

	while (1)
	{
		read_line = get_next_line(fd);
		if (!read_line)
			break ;
		tmp = *line;
		*line = ft_strjoin(*line, read_line);
		free(tmp);
		free(read_line);
	}
}

void	set_z_limits(t_point ***points, t_vars *vars)
{
	int	y;
	int	x;
	int	cols;
	int	rows;

	vars->min_z = 0;
	vars->max_z = 0;
	rows = points[0][0]->info->rows;
	cols = points[0][0]->info->cols;
	y = -1;
	while (++y < rows)
	{
		x = -1;
		while (++x < cols)
		{
			if (vars->min_z > points[y][x]->z)
				vars->min_z = points[y][x]->z;
			if (vars->max_z < points[y][x]->z)
				vars->max_z = points[y][x]->z;
		}
	}
}
