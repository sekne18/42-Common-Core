/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jans <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 23:32:34 by jans              #+#    #+#             */
/*   Updated: 2024/10/28 10:50:36 by jans             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	main(int argc, char **argv)
{
	char	**map;
	t_vars	*vars;

	map = NULL;
	if (argc != 2)
		return (0);
	if (parse_map(&map, argv[1]) == 0)
		return (0);
	if (!init_vars(&vars))
	{
		cleanup(vars);
		free_all(map);
		return (0);
	}
	vars->points = get_points_array(map, vars);
	free_all(map);
	if (!vars->points)
		return (0);
	ft_hook_init(vars);
	ft_draw(vars);
	mlx_loop(vars->mlx);
	cleanup(vars);
	return (0);
}

int	ft_draw(t_vars *vars)
{
	if (!vars || !vars->points)
		return (0);
	draw_wireframe(vars->points, vars);
	mlx_put_image_to_window(vars->mlx, vars->win, vars->data->img, 0, 0);
	return (1);
}
