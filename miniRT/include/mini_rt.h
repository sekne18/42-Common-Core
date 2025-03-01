/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_rt.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmol <fmol@student.s19.be>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/26 15:15:16 by fmol              #+#    #+#             */
/*   Updated: 2025/02/18 15:15:23 by fmol             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINI_RT_H
# define MINI_RT_H

# include "scene.h"
# include "loader.h"
# include "raytracer.h"
# include "parsing.h"
# include "vector.h"
# include "libft.h"
# include "keycodes.h"
# include <mlx.h>
# include <unistd.h>
# include <stdlib.h>

# define NR_SAMPLES 1 
# define NR_FRAMES 1000
# define SAVE_BUFFER_SIZE 4096
# define ON_DESTROY	17

# define COLOR_BVH_R 0.5
# define COLOR_BVH_G 0.0
# define COLOR_BVH_B 0.0
# define COLOR_BVH_MESH_R 0.0
# define COLOR_BVH_MESH_G 0.0
# define COLOR_BVH_MESH_B 0.5

typedef struct s_img
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
	int		width;
	int		height;
}				t_img;

typedef struct s_frame
{
	int		w;
	int		h;
	int		frame_nr;
	float	progress;
}			t_frame;

typedef struct window
{
	void		*mlx;
	void		*win;
	t_img		*img[2];
	int			total_frame_nr;
	t_frame		frame;
	t_context	context;
	int			update;
	int			display_bvh;
}				t_window;

typedef struct s_pixel_data
{
	t_window	*window;
	char		*buffer;
	size_t		*k;
	int			fd;
}	t_pixel_data;

t_img	*create_img(void *mlx_ptr, int width, int height);
void	copy_img(t_img *dest, t_img *src);
void	avg_img(t_img *acc, t_img *new, int frame_nr);
void	clear_img(t_img *img);
void	my_mlx_pixel_put(t_img *img, int x, int y, int color);

int		save_render(t_window *window, char *filename);
int		load_scene(t_context *context, char *filename);

int		build_sphere(t_context *context, char **values,
			t_list *mtl_ids, int index);
int		build_plane(t_context *context, char **values,
			t_list *mtl_ids, int index);
int		build_quad(t_context *context, char **values,
			t_list *mtl_ids, int index);
int		build_cylinder(t_context *context, char **values,
			t_list *mtl_ids, int index);
int		build_triangle(t_context *context, char **values,
			t_list *mtl_ids, int index);
int		build_disk(t_context *context, char **values,
			t_list *mtl_ids, int index);
int		build_mesh(t_context *context, char **values,
			t_list *mtl_ids, int index);
int		build_material(t_context *context, char **values,
			t_list *mtl_ids);
int		build_materials(t_context *context, char *line,
			t_list *mtl_ids);
int		build_objects(t_context *context, char *line,
			t_list *mtl_ids, t_obj_count *count);
int		build_camera(t_context *context, char *line);
int		build_amb_light(t_context *context, char *line);
int		build_window(t_context *context, char *line);

int		first_pass(t_context *context, char *filename,
			t_obj_count *obj_counts, t_list **mtl_ids);
int		second_pass(t_context *context, char *filename,
			t_list *mtl_ids, t_obj_count *obj_counts);

int		render(t_window *window);

float	to_radians(float degrees);
float	to_degrees(float radians);

void	cleanup_window(t_window *window);

t_vec3	trace_bvh(t_ray *ray, t_bvh *bvh, t_scene *scene);

#endif // MINI_RT_H
