/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jans <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 23:32:34 by jans              #+#    #+#             */
/*   Updated: 2024/11/25 19:29:24 by jsekne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	main(int argc, char **argv)
{
	char	**map;
	t_vars	*vars;

	vars = NULL;
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
	if (get_points_array(map, vars))
	{
		ft_hook_init(vars);
		ft_draw(vars);
		mlx_loop(vars->mlx);
	}
	free_all(map);
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
