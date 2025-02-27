/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmol <fmol@student.s19.be>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 07:44:59 by fmol              #+#    #+#             */
/*   Updated: 2025/02/13 10:57:09 by fmol             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

void	calc_pixel_color(t_window *window, t_vec3 *color)
{
	t_vec3			tmp;
	int				i;
	t_ray			ray;
	unsigned int	seed;

	*color = (t_vec3){{0.0, 0.0, 0.0}};
	seed = window->frame.w + window->frame.h * window->context.camera->width
		+ window->total_frame_nr * 3 * window->context.camera->width
		* window->context.camera->height;
	i = 0;
	while (i++ < NR_SAMPLES)
	{
		calc_jittered_ray(&ray, window->context.camera,
			(t_vec2){window->frame.w, window->frame.h}, &seed);
		tmp = pathtrace(ray, window->context.scene, &seed);
		add_local(color, &tmp);
	}
	div_scalar_local(color, NR_SAMPLES);
	if (!window->display_bvh)
		return ;
	calc_ray(&ray, window->context.camera, window->frame.w, window->frame.h);
	tmp = trace_bvh(&ray, window->context.scene->bvh, window->context.scene);
	add_local(color, &tmp);
}

int	render_next_pixel(t_window *window)
{
	t_vec3	color;

	if (window->frame.h < window->context.height
		&& window->frame.w < window->context.width)
	{
		calc_pixel_color(window, &color);
		my_mlx_pixel_put(window->img[1],
			window->frame.w,
			window->frame.h,
			vec3_to_int(&color));
		window->frame.w++;
	}
	if (window->frame.h >= window->context.height - 1
		&& window->frame.w >= window->context.width)
	{
		window->frame.w = 0;
		window->frame.h = 0;
	}
	else if (window->frame.w >= window->context.width)
	{
		window->frame.w = 0;
		window->frame.h++;
	}
	return (0);
}

int	render_n_next_pixels(t_window *window, int n)
{
	int	i;

	i = -1;
	while (++i < n)
		render_next_pixel(window);
	return (0);
}

int	render(t_window *window)
{
	if (window->update || window->frame.frame_nr < NR_FRAMES)
		render_n_next_pixels(window, window->context.width
			* window->context.height);
	if (window->update)
	{
		copy_img(window->img[0], window->img[1]);
		window->total_frame_nr++;
		window->frame.frame_nr = 0;
		window->frame.w = 0;
		window->frame.h = 0;
		window->update = 0;
	}
	else if (window->frame.frame_nr < NR_FRAMES)
	{
		if (!window->frame.frame_nr)
			copy_img(window->img[0], window->img[1]);
		else
			avg_img(window->img[0], window->img[1], window->frame.frame_nr);
		window->frame.frame_nr++;
		window->total_frame_nr++;
	}
	mlx_put_image_to_window(window->mlx, window->win, window->img[0]->img,
		0, 0);
	return (0);
}
