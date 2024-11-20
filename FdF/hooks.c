/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jans <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/26 07:42:14 by jans              #+#    #+#             */
/*   Updated: 2024/11/20 11:23:19 by jsekne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <stdio.h>

int	ft_close_win(void *param)
{
	cleanup(param);
	exit(0);
}

int	ft_key_press(int keycode, void *param)
{
	t_vars	*vars;

	vars = param;
	if (keycode == ESCAPE)
		ft_close_win(vars);
	else if (keycode == KEY_A)
		vars->angle_y -= 0.1;
	else if (keycode == KEY_D)
		vars->angle_y += 0.1;
	else if (keycode == KEY_W)
		vars->angle_x += 0.1;
	else if (keycode == KEY_S)
		vars->angle_x += 0.1;
	else if (keycode == KEY_Q)
		vars->angle_y -= 0.1;
	else if (keycode == KEY_E)
		vars->angle_y += 0.1;
	ft_draw(vars);
	return (0);
}

int	ft_mouse_button(int button, int x, int y, void *params)
{
	t_vars	*vars;

	(void)y;
	(void)x;
	vars = params;
	if (button == 4)
		vars->zoom++;
	else if (button == 5)
		vars->zoom--;
	if (vars->zoom < 1)
		vars->zoom = 1;
	ft_draw(vars);
	return (0);
}

int	init_vars(t_vars **vars)
{
	*vars = malloc(sizeof(t_vars));
	if (!*vars)
		return (0);
	(*vars)->data = malloc(sizeof(t_data));
	if (!(*vars)->data)
		return (0);
	init_mlx(*vars);
	return (1);
}

void	init_mlx(t_vars *vars)
{
	vars->mlx = mlx_init();
	vars->win = mlx_new_window(vars->mlx, WIN_WIDTH, WIN_HEIGHT, "FdF");
	vars->data->img = mlx_new_image(vars->mlx, WIN_WIDTH, WIN_HEIGHT);
	vars->data->addr = mlx_get_data_addr(vars->data->img,
			&vars->data->bits_per_pixel, &vars->data->line_length,
			&vars->data->endian);
	vars->points = NULL;
	vars->zoom = 4;
	vars->angle_x = 0;
	vars->angle_y = 0;
	vars->angle_z = M_PI / 6;
}

void	ft_hook_init(t_vars *vars)
{
	mlx_hook(vars->win, 2, 1L << 0, ft_key_press, vars);
	mlx_hook(vars->win, 17, 0, ft_close_win, vars);
	mlx_hook(vars->win, 4, 0, ft_mouse_button, vars);
	mlx_hook(vars->win, 5, 0, ft_mouse_button, vars);
	mlx_mouse_hook(vars->win, ft_mouse_button, vars);
}
