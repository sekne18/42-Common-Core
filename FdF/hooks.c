/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jans <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/26 07:42:14 by jans              #+#    #+#             */
/*   Updated: 2024/11/26 11:13:42 by jsekne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	init_vars(t_vars **vars)
{
	*vars = malloc(sizeof(t_vars));
	if (!*vars)
		return (0);
	ft_memset(*vars, 0, sizeof(t_vars));
	(*vars)->data = malloc(sizeof(t_data));
	if (!(*vars)->data)
		return (0);
	(*vars)->win = NULL;
	(*vars)->data->img = NULL;
	(*vars)->data->addr = NULL;
	if (!init_mlx(*vars))
		return (0);
	return (1);
}

int	init_mlx(t_vars *vars)
{
	vars->mlx = mlx_init();
	if (!vars->mlx)
		return (0);
	vars->win = mlx_new_window(vars->mlx, WIN_WIDTH, WIN_HEIGHT, "FdF");
	if (!vars->win)
		return (0);
	vars->data->img = mlx_new_image(vars->mlx, WIN_WIDTH, WIN_HEIGHT);
	if (!vars->data->img)
		return (0);
	vars->data->addr = mlx_get_data_addr(vars->data->img,
			&vars->data->bits_per_pixel,
			&vars->data->line_length,
			&vars->data->endian);
	if (!vars->data->addr)
		return (0);
	vars->info = ft_new_info(0, 0);
	if (!vars->info)
		return (0);
	vars->points = NULL;
	vars->zoom = 4;
	vars->angle = M_PI / 6;
	vars->transl = 0;
	return (1);
}

void	ft_hook_init(t_vars *vars)
{
	mlx_hook(vars->win, 2, 1L << 0, ft_key_press, vars);
	mlx_hook(vars->win, 17, 0, ft_close_win, vars);
	mlx_hook(vars->win, 4, 0, ft_mouse_button, vars);
	mlx_mouse_hook(vars->win, ft_mouse_button, vars);
}
