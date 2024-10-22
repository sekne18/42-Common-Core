/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jans <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 23:32:34 by jans              #+#    #+#             */
/*   Updated: 2024/10/22 14:31:38 by jsekne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

typedef struct	s_data {
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}				t_data;

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

void	draw_line(int *x_pos, int *y_pos, t_data *img, char axis);

void	fdf(char **map)
{
	void	*mlx;
	void	*mlx_win;
	int		len_x;
	int		len_y;
	int		x;
	int		y;
	int		**map_i;
	t_data	img;

	len_x = 0;
	len_y = 0;
	//Converts char arr to int arr
	map_i = to_int_array(map, &len_x, &len_y);
	mlx = mlx_init();
	mlx_win = mlx_new_window(mlx, 700, 700, "FdF");
	img.img = mlx_new_image(mlx, 700, 700);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length,
										&img.endian);
	int	x_pos;
	int y_pos;
	y = 0;
	y_pos = 20;
	while (y++ < len_y)
	{
		x_pos = 20;
		x = 0;
		while (x++ < len_x)
			draw_line(&x_pos, &y_pos, &img, 'x');
		y_pos += 20;
	}
	x_pos = 20;
	x = 0;
	while (x++ < len_x)
	{
		y_pos = 20;
		y = 0;
		while (y++ < len_y)
			draw_line(&x_pos, &y_pos, &img, 'y');
		x_pos += 20;
	}
	mlx_put_image_to_window(mlx, mlx_win, img.img, 25, 25);
	mlx_loop(mlx);
}

void	draw_line(int *x_pos, int *y_pos, t_data *img, char axis)
{
	int	i;
	
	i = -1;
	while (++i < 20)
	{
		if (axis == 'x')
			my_mlx_pixel_put(img, (*x_pos)++, *y_pos, 0x00FF0000);
		else	
			my_mlx_pixel_put(img, *x_pos, (*y_pos)++, 0x00FF0000);
	}
}

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
