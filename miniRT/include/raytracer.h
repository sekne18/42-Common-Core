/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytracer.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmol <fmol@student.s19.be>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/26 14:50:04 by fmol              #+#    #+#             */
/*   Updated: 2025/02/18 16:36:19 by fmol             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAYTRACER_H
# define RAYTRACER_H

# include "scene.h"
# include "vector.h"
# include "libft.h"
# include "lerp.h"

# define INV_COLOR 0.00392156862
# define FLT_MAX 3.402823e+38
# define FLT_MIN 1.175494e-38

# define MAX_BOUNCES 100
# define JITTER 0.01 //0.1 for blur
# define JITTER_FOCUS 0.0
# define MIN_ZOOM 1.0
# define MAX_ZOOM 10.0

# define ATMOSPHERE_HIGH_R 0.1
# define ATMOSPHERE_HIGH_G 0.3
# define ATMOSPHERE_HIGH_B 0.6
# define ATMOSPHERE_MID_R 0.05
# define ATMOSPHERE_MID_G 0.15
# define ATMOSPHERE_MID_B 0.3
# define ATMOSPHERE_LOW_R 0.0
# define ATMOSPHERE_LOW_G 0.0
# define ATMOSPHERE_LOW_B 0.0
//nice atmospheres:
//blood moon: HIGH: 0.5, 0.0, 0.0, LOW: 0.0, 0.0, 0.3
//bright sky: HIGH: 0.5, 0.7, 1.0, LOW: 1.0, 1.0, 1.0

typedef struct s_ray
{
	t_vec3	origin;
	t_vec3	direction;
	t_vec3	invdir;
}				t_ray;

/*	   - viewport -		*/
/*	* ------ > vec3 u	*/
/*	| . . . . . . . .	*/
/*	| . . . . . . . .	*/
/*	| . . . . . . . .	*/
/*	⌄ . . . . . . . .	*/
/*	vec3 v				*/

typedef struct s_viewport
{
	float	aspect_ratio;
	t_vec3	u; // defines horizontal direction = normalized 
	t_vec3	v; // defines vertical direction = normalized
	float	delta_u; // = u * viewport_width / width
	float	delta_v; // = v * viewport_height / height
	t_vec3	upper_left_corner;
}			t_viewport;

typedef struct s_camera
{
	t_vec3		origin;
	t_vec3		direction;
	t_quat		orientation;
	float		hfov;
	float		zoom;
	int			width;
	int			height;
	t_viewport	*viewport;
}				t_camera;

typedef struct s_context
{
	int			width;
	int			height;
	t_camera	*camera;
	t_scene		*scene;
}				t_context;

typedef struct s_hit_record
{
	int				hit;
	t_vec3			point;
	t_vec3			normal;
	t_vec2			uv;
	float			t;
	t_object_type	type;
	t_material		*material;
}				t_hit_record;

typedef struct s_mesh_hit_test
{
	t_ray			*ray;
	t_scene			*scene;
	t_hit_record	*record;
	t_mesh			*mesh;
	t_bvh_node		*current;
	unsigned int	mesh_i;
}			t_mesh_hit_test;

t_vec3			int_to_vec3(int color);
int				vec3_to_int(t_vec3 *color);
int				color_mul(int color, int mul);
int				color_add(int color, int add);
int				rgb_mul(int color, float r, float g, float b);
int				color_scale(int color, float scale);
int				rgb_add(int color, float r, float g, float b);
int				rgb_to_int(float r, float g, float b);
void			int_to_rgb(int color, float *r, float *g, float *b);

void			cleanup_camera(t_camera *camera);
int				init_camera(t_context *context, t_vec3 origin,
					t_vec3 direction, float hfov);
void			set_camera_orientation(t_camera *c, t_vec3 *direction);
void			translate_camera(t_camera *c, t_vec3 *translation);
void			translate_camera_forward(t_camera *c, float distance);
void			translate_camera_up(t_camera *c, float distance);
void			translate_camera_right(t_camera *c, float distance);
void			rotate_camera(t_camera *c, t_vec3 axis, float angle);
void			rotate_camera_roll(t_camera *c, float angle);
void			rotate_camera_yaw(t_camera *c, float angle);
void			rotate_camera_pitch(t_camera *c, float angle);
void			adjust_camera_zoom(t_camera *c, float zoom);

float			random_float(unsigned int *seed);
t_vec3			random_unit_vec(unsigned int *seed);
t_vec3			random_hemisphere_vec(const t_vec3 *restrict normal,
					unsigned int *seed);
t_vec2			random_circle_vec(unsigned int *seed);

t_vec3			get_viewpoint(t_camera *c, int x, int y);
void			jitter_ray(t_ray *ray, t_camera *c, unsigned int *seed);
t_vec3			jitter_point(t_vec3 point, unsigned int *seed, t_camera *c);
t_vec3			calc_ray_dir(t_vec3 origin, t_vec3 viewpoint);

float			hit_bbox(t_ray *ray, t_aabb *box);
void			intersect_bvh(t_ray *ray, t_scene *scene, t_hit_record *record);

void			invert_normal(t_vec3 *normal, t_ray *ray);
float			hit_face(t_ray *ray, t_face *face, t_vec3 *vertices,
					t_vec3 *edges);
void			fill_face_record(t_hit_record *record, t_ray *ray, float t);
void			set_face_normal(t_hit_record *record, t_mesh *mesh,
					unsigned int *indices);

void			set_uv(t_hit_record *record);
t_vec3			get_texture_color(t_material *mtl, t_vec2 *uv,
					t_vec3 *point, t_object_type type);
t_vec3			sample_texture(t_txt_img *img, float u, float v);
void			adjust_texture_normal(t_hit_record *record);

void			fill_triangle_record(t_hit_record *record,
					t_ray *ray, t_object *obj, float t);
void			fill_cylinder_record(t_hit_record *record,
					t_ray *ray, t_object *obj, float t);
void			fill_record(t_hit_record *record, t_ray *ray,
					t_object *obj, float t);

float			hit_sphere(t_ray *ray, t_sphere *sphere);
float			hit_plane(t_ray *ray, t_plane *plane);
float			hit_quad(t_ray *ray, t_quad *quad);
float			hit_disk(t_ray *ray, t_disk *disk);
float			hit_cylinder(t_ray *ray, t_cylinder *cylinder);
float			hit_triangle(t_ray *ray, t_triangle *triangle);
float			check_hit(t_ray *ray, t_object *obj);
t_hit_record	get_hit(t_ray *ray, t_scene *scene);
t_vec3			*ray_at(t_vec3 *res, t_ray *ray, float t);
void			calc_jittered_ray(t_ray *ray, t_camera *c, t_vec2 coords,
					unsigned int *seed);
void			calc_ray(t_ray *ray, t_camera *c, int x, int y);
float			set_bounce_ray_dir(t_ray *ray, const t_hit_record *record,
					unsigned int *seed);
t_vec3			pathtrace(t_ray ray, t_scene *scene, unsigned int *seed);

#endif // RAYTRACER_H
