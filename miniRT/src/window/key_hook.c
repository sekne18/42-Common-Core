/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_hook.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmol <fmol@student.s19.be>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 13:15:21 by fmol              #+#    #+#             */
/*   Updated: 2025/02/12 13:15:41 by fmol             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

#ifdef __LINUX__

void	cleanup_window(t_window *window)
{
	if (!window)
		return ;
	if (window->img[0])
	{
		if (window->img[0]->img)
			mlx_destroy_image(window->mlx, window->img[0]->img);
		free(window->img[0]);
	}
	if (window->img[1])
	{
		if (window->img[1]->img)
			mlx_destroy_image(window->mlx, window->img[1]->img);
		free(window->img[1]);
	}
	if (window->win)
		mlx_destroy_window(window->mlx, window->win);
	if (window->mlx)
		mlx_destroy_display(window->mlx);
	free(window->mlx);
	cleanup_camera(window->context.camera);
	cleanup_scene(window->context.scene);
	free(window);
}

#elif defined(__DARWIN__)

void	cleanup_window(t_window *window)
{
	if (!window)
		return ;
	if (window->img[0])
	{
		if (window->img[0]->img)
			mlx_destroy_image(window->mlx, window->img[0]->img);
		free(window->img[0]);
	}
	if (window->img[1])
	{
		if (window->img[1]->img)
			mlx_destroy_image(window->mlx, window->img[1]->img);
		free(window->img[1]);
	}
	if (window->win)
		mlx_destroy_window(window->mlx, window->win);
	cleanup_camera(window->context.camera);
	cleanup_scene(window->context.scene);
	free(window);
}
#endif