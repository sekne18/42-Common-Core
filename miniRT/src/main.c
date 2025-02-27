/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmol <fmol@student.s19.be>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/26 14:32:51 by fmol              #+#    #+#             */
/*   Updated: 2025/02/19 10:30:05 by fmol             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

int	quit(t_window *window)
{
	cleanup_window(window);
	exit(0);
}

static inline void	do_rotate(int keycode, t_camera *camera)
{
	if (keycode == KEY_YAW_L)
		rotate_camera_yaw(camera, to_radians(10));
	else if (keycode == KEY_PITCH_UP)
		rotate_camera_pitch(camera, to_radians(10));
	else if (keycode == KEY_YAW_R)
		rotate_camera_yaw(camera, to_radians(-10));
	else if (keycode == KEY_ROLL_R)
		rotate_camera_roll(camera, to_radians(-10));
	else if (keycode == KEY_PITCH_DOWN)
		rotate_camera_pitch(camera, to_radians(-10));
	else if (keycode == KEY_ROLL_L)
		rotate_camera_roll(camera, to_radians(10));
}

int	key_hook(int keycode, t_window *window)
{
	window->update = 1;
	if (keycode == KEY_ESC)
		quit(window);
	else if (keycode == KEY_SAVE)
		window->display_bvh = !window->display_bvh;
	else if (keycode == KEY_FORWARD)
		translate_camera_forward(window->context.camera, 1);
	else if (keycode == KEY_BACK)
		translate_camera_forward(window->context.camera, -1);
	else if (keycode == KEY_LEFT)
		translate_camera_right(window->context.camera, -1);
	else if (keycode == KEY_RIGHT)
		translate_camera_right(window->context.camera, 1);
	else if (keycode == KEY_UP)
		translate_camera_up(window->context.camera, 1);
	else if (keycode == KEY_DOWN)
		translate_camera_up(window->context.camera, -1);
	else if (keycode == KEY_ZOOMIN)
		adjust_camera_zoom(window->context.camera, 1);
	else if (keycode == KEY_ZOOMOUT)
		adjust_camera_zoom(window->context.camera, -1);
	do_rotate(keycode, window->context.camera);
	return (0);
}

int	init_window(t_window *window, char *filename)
{
	if (load_scene(&window->context, filename) != SUCCESS)
		return (0);
	if (!build_bvh(window->context.scene))
		return (cleanup_scene(window->context.scene), 0);
	window->total_frame_nr = 0;
	window->frame.frame_nr = 0;
	window->frame.w = 0;
	window->frame.h = 0;
	window->mlx = mlx_init();
	window->win = mlx_new_window(window->mlx,
			window->context.width, window->context.height, "miniRT");
	if (!window->mlx || !window->win)
		return (0);
	window->img[0] = create_img(window->mlx,
			window->context.width, window->context.height);
	window->img[1] = create_img(window->mlx,
			window->context.width, window->context.height);
	if (!window->img[0] || !window->img[1])
		return (0);
	return (1);
}

int	main(int argc, char **argv)
{
	t_window	*window;

	if (argc != 2)
		return (ft_putendl_fd("Usage: ./miniRT scene.rt", 1), 1);
	window = calloc(1, sizeof(t_window));
	window->update = 1;
	window->display_bvh = 0;
	if (!window || !init_window(window, argv[1]))
		return (cleanup_window(window), 1);
	mlx_put_image_to_window(window->mlx, window->win,
		window->img[0]->img, 0, 0);
	mlx_key_hook(window->win, key_hook, window);
	mlx_hook(window->win, ON_DESTROY, 0, quit, window);
	mlx_loop_hook(window->mlx, render, window);
	mlx_loop(window->mlx);
	return (cleanup_window(window), 0);
}
