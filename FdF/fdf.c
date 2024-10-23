/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jans <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 23:32:34 by jans              #+#    #+#             */
/*   Updated: 2024/10/23 16:41:41 by jsekne           ###   ########.fr       */
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
	
	mlx = mlx_init();
	mlx_win = mlx_new_window(mlx, 700, 700, "FdF");
	img.img = mlx_new_image(mlx, 700, 700);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length,
										&img.endian);
	initialize(map, &img);
	
	mlx_put_image_to_window(mlx, mlx_win, img.img, 25, 25);
	mlx_loop(mlx);
}

void	initialize(char **map, t_data *img)
{
	t_point	***points;

	points = get_points_array(map);
	if (!points)
		return ;
	draw_wireframe(points, img);
}

int projected_x(t_point *p)
{
	return (p->x - p->y) * cos(((M_PI / 180) * 30));	
}

int projected_y(t_point *p)
{	
	return (p->x + p->y) * sin(((M_PI / 180) * 30)) - p->z;
}
