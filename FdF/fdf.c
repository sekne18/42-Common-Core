/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jans <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 23:32:34 by jans              #+#    #+#             */
/*   Updated: 2024/10/24 22:59:40 by jans             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	fdf(char **map)
{
	t_vars	vars;
	t_data	img;
	
	vars.mlx = mlx_init();
	vars.win = mlx_new_window(vars.mlx, WIN_HEIGHT, WIN_WIDTH, "FdF");
	img.img = mlx_new_image(vars.mlx, WIN_HEIGHT, WIN_WIDTH);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length,
										&img.endian);
	mlx_key_hook(vars.win, key_hook, &vars);
	mlx_mouse_hook(vars.win, mouse_hook, &vars);
	initialize(map, &img);
	mlx_put_image_to_window(vars.mlx, vars.win, img.img, 50, 50);
	mlx_loop(vars.mlx);
}

void	initialize(char **map, t_data *img)
{
	t_point	***points;

	points = get_points_array(map);
	if (!points)
		return ;
	draw_wireframe(points, img);
}
