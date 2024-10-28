/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jans <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/26 07:42:14 by jans              #+#    #+#             */
/*   Updated: 2024/10/28 11:36:09 by jans             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

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
}

void	ft_hook_init(t_vars *vars)
{
	mlx_hook(vars->win, 2, 1L << 0, ft_key_press, vars);
	mlx_hook(vars->win, 17, 0, ft_close_win, vars);
}
