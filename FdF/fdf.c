/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jans <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 23:32:34 by jans              #+#    #+#             */
/*   Updated: 2024/10/22 22:14:04 by jans             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

void	fdf(char **map)
{
	void	*mlx;
	void	*mlx_win;
	t_data	img;
	t_point	**points;
	
	mlx = mlx_init();
	mlx_win = mlx_new_window(mlx, 700, 700, "FdF");
	img.img = mlx_new_image(mlx, 700, 700);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length,
										&img.endian);
	points = convert_to_points(map);
	recalc_points(points);
	mlx_put_image_to_window(mlx, mlx_win, img.img, 25, 25);
	mlx_loop(mlx);
}

t_point	**convert_to_points(char **map)
{
	int		len_x;
	int		len_y;
	int		**map_i;
	t_point	**points;

	len_x = 0;
	len_y = 0;
	map_i = to_int_array(map, &len_x, &len_y);
	while (len_y--)
	{
		while (len_x--)
			ft_lstadd_back(points, ft_lstnew(len_y, len_x, map_i[len_y][len_x]));
	}
	return (points);
}

void	recalc_points(t_point **points)
{
	t_point	*head;

	if (!*points)
		return (0);
	head = *points;
	while (head)
	{
		head->x = head->x * cos() + head->y * cos( + 2) + head->z * cos( - 2);
		head->y = head->x * cos() + head->y * cos( + 2) + head->z * cos( - 2);
		head = head->next;
	}
}
/*void	draw_line(int *x_pos, int *y_pos, t_data *img, char axis)
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
}*/
