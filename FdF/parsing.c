/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jans <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 20:53:12 by jans              #+#    #+#             */
/*   Updated: 2024/10/22 21:49:38 by jans             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	**to_int_array(char **map, int *len_x, int *len_y)
{
	int	**arr;
	int	i;

	i = 0;
	if (!map)
		return (NULL);
	while (map[*len_y])
		(*len_y)++;
	arr = malloc((*len_y + 1) * sizeof(int *));
	if (!arr)
		return (NULL);
	i = -1;
	while (map[++i])
		arr[i] = get_int_arr_line(map[i], len_x);
	arr[i] = 0;
	return (arr);
}

int	*get_int_arr_line(char *line, int *len_x)
{
	char	**formatted;
	int		i;
	int		*int_arr;

	i = -1;
	formatted = ft_split(line, ' ');
	if (!formatted)
		return (NULL);
	while (formatted[*len_x])
		(*len_x)++;
	int_arr = malloc(*len_x * sizeof(int));
	if (!int_arr)
		return (NULL);
	while (formatted[++i])
		int_arr[i] = ft_atoi(formatted[i]);
	free_all(formatted);
	return (int_arr);
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
