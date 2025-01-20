/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jans <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 20:53:12 by jans              #+#    #+#             */
/*   Updated: 2024/11/26 13:48:32 by jsekne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	get_points_array(char **map, t_vars *vars)
{
	int	i;
	int	len_y;

	len_y = 0;
	i = 0;
	if (!map)
		return (0);
	while (map[len_y])
		len_y++;
	vars->points = malloc(len_y * sizeof(t_point **));
	if (!vars->points)
		return (0);
	vars->info->rows = len_y;
	i = -1;
	while (map[++i])
	{
		vars->points[i] = get_cols(map[i], i, vars);
		if (!vars->points[i])
			return (0);
	}
	set_z_limits(vars->points, vars);
	return (1);
}

t_point	**get_cols(char *line, int y, t_vars *vars)
{
	char	**formatted;
	t_point	**point_arr;
	int		len_x;

	len_x = 0;
	formatted = ft_split(line, ' ');
	if (!formatted)
		return (NULL);
	len_x = ft_2dstrlen(formatted);
	point_arr = populate_points(formatted, y, vars, len_x);
	free_all(formatted, 1);
	return (point_arr);
}

t_point	**populate_points(char **formatted, int y, t_vars *vars, int len_x)
{
	t_point	**point_arr;
	int		x;

	point_arr = allocate_points(len_x);
	if (!point_arr)
		return (NULL);
	x = -1;
	while (formatted[++x])
	{
		point_arr[x] = ft_new_point(x, y, ft_atoi(formatted[x]));
		if (!point_arr[x])
		{
			vars->info->cols = x;
			free_point_array(point_arr, x);
			return (NULL);
		}
	}
	vars->info->cols = x;
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
	if (!get_lines(fd, &line))
	{
		close(fd);
		free(line);
		return (0);
	}
	close(fd);
	*map = ft_split(line, '\n');
	free(line);
	return (1);
}

int	get_lines(int fd, char **line)
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
		if (!*line)
		{
			free_all(line, 0);
			free(tmp);
			free(read_line);
			return (0);
		}
		free(tmp);
		free(read_line);
	}
	return (1);
}
