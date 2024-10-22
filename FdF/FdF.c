/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   FdF.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jans <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 23:32:34 by jans              #+#    #+#             */
/*   Updated: 2024/10/22 10:49:09 by jsekne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Fdf.h"

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

void	fdf(char	**map)
{
	void	*mlx;
	void	*mlx_win;
	int		x;
	int		y;
	t_data	img;

	mlx = mlx_init();
	mlx_win = mlx_new_window(mlx, 700, 700, "FdF");
	img.img = mlx_new_image(mlx, 700, 700);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length,
										&img.endian);
	int	x_pos;
	int y_pos;
	y = -1;
	while (map[++y])
	{
		x_pos = 20;
		x = -1;
		while (map[++x])
			draw_line(x_pos, y_pos, &img, 'x');
		y_pos += 20;
	}
	y = -1;
	while (map[++y])
	{
		y_pos = 20;
		x = -1;
		while (map[++x])
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
			my_mlx_pixel_put(img, (*x_pos)++, *y_pos, 0x00000000);
		else	
			my_mlx_pixel_put(img, *x_pos, (*y_pos)++, 0x00000000);
	}
}