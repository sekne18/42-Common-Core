/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmol <fmol@student.s19.be>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/26 14:49:17 by fmol              #+#    #+#             */
/*   Updated: 2025/02/19 08:54:01 by fmol             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SCENE_H
# define SCENE_H

# include "vector.h"
# include "libft.h"
# include <fcntl.h> //should be removed
# include <stdio.h> //should be removed
# include "bvh.h"

# define BUMP_STRENGTH 20.0f

typedef enum e_texture_type
{
	T_NONE = 0,
	T_CHECKERBOARD,
	T_IMAGE,
	T_BUMP,
	T_IMG_AND_BUMP
}			t_texture_type;

typedef struct s_txt_img
{
	unsigned char	*data;
	int				width;
	int				height;
}			t_txt_img;

typedef struct s_texture
{
	t_texture_type	type;
	void			*data;
}			t_texture;

typedef struct s_material
{
	t_vec3		ambient;
	t_vec3		diffuse;
	t_vec3		specular;
	t_vec3		emission;
	float		emission_intensity;
	float		smoothness;
	float		specular_intensity;
	float		refraction_intensity;
	float		refractive_index;
	t_texture	*texture;
}			t_material;

typedef struct s_transform
{
	t_vec3	position;
	t_vec3	rotation;
	t_vec3	scale;
}			t_transform;

typedef struct s_sphere
{
	t_vec3		center;
	float		radius;
}			t_sphere;

typedef struct s_plane
{
	t_vec3		normal;
	t_vec3		point;
}			t_plane;

//normal: computed from u and v, but stored for performance
//w: computed from normal / dot(normal, normal), but stored for performance
typedef struct s_quad
{
	t_vec3		point;
	t_vec3		u;
	t_vec3		v;
	t_vec3		normal;
	t_vec3		w;
}			t_quad;

typedef struct s_triangle
{
	t_vec3		vertices[3];
	t_vec3		edge1; // stored for performance
	t_vec3		edge2; // stored for performance
	t_vec3		normal;
}			t_triangle;

typedef struct s_face
{
	unsigned int	vertices[3];
	//unsigned int	normals[3];
	//unsigned int	uv[3];
}			t_face;

typedef struct s_mesh
{
	t_vec3			*vertices;
	t_vec3			*normals;
	//t_vec2			*uv;
	t_face			*faces;
	t_vec3			*face_edges;
	unsigned int	vertex_count;
	unsigned int	normal_count;
	unsigned int	uv_count;
	unsigned int	face_count;
}			t_mesh;

typedef struct s_disk
{
	t_vec3		center;
	t_vec3		normal;
	float		radius;
}			t_disk;

typedef struct s_cylinder
{
	t_vec3		center;
	t_vec3		base; // stored for performance
	t_vec3		axis;
	float		radius;
	float		height;
}			t_cylinder;

typedef enum e_object_type
{
	SPHERE = 1,
	PLANE,
	QUAD,
	DISK,
	CYLINDER,
	TRIANGLE,
	MESH
}			t_object_type;

typedef struct s_object
{
	t_material		*material;
	t_object_type	type;
	t_aabb			bbox;
	t_vec3			center;
	void			*data;
}			t_object;

typedef struct s_scene
{
	t_bvh			*bvh;
	t_material		*materials;
	t_object		*objects;
	t_vec3			*amb_light;
	unsigned int	amb_light_count;
	unsigned int	object_count;
	unsigned int	mesh_count;
	unsigned int	plane_count;
	unsigned int	material_count;
}				t_scene;

typedef struct s_split_primitives_params
{
	t_bvh_node		*node;
	t_mesh_bvh		*mesh_bvh;
	float			split_pos;
	int				best_axis;
	t_bvh_node		*left;
	t_bvh_node		*right;

}					t_split_primitives_params;

t_aabb		get_sphere_aabb(t_sphere *sphere);
t_aabb		get_plane_aabb(t_plane *plane);
t_aabb		get_quad_aabb(t_quad *quad);
t_aabb		get_triangle_aabb(t_triangle *triangle);
t_aabb		get_disk_aabb(t_disk *disk);
t_aabb		get_cylinder_aabb(t_cylinder *cylinder);
t_aabb		get_mesh_aabb(t_mesh *mesh);

int			build_mesh_bvh(t_scene *scene, unsigned int mesh_i);
int			build_bvh(t_scene *scene);

void		cleanup_scene(t_scene *scene);
int			init_scene(t_scene *scene);

t_object	create_sphere(t_vec3 center, float radius);
t_object	create_plane(t_vec3 normal, t_vec3 point);
t_object	create_cylinder(t_vec3 center,
				t_vec3 orientation, float radius, float height);
t_object	create_triangle(t_vec3 vertices[3]);
t_object	create_quad(t_vec3 point, t_vec3 u, t_vec3 v);
t_object	create_disk(t_vec3 center, t_vec3 normal, float radius);
t_object	create_mesh(t_vec3 anchor_point,
				t_vec3 scale, t_quat *rotation, t_mesh *mesh);

t_vec3		get_mesh_center(t_mesh *mesh);
void		destroy_mesh(t_mesh *mesh);
void		destroy_texture(t_texture *texture);

int			calc_mesh_best_axis(t_bvh_node *node, t_mesh_bvh *mesh,
				float *split_pos, float parent_cost);
int			add_children_mesh(unsigned int i, t_mesh_bvh *mesh_bvh,
				int best_axis, float split_pos);
int			set_root_bvh_mesh(t_scene *scene, unsigned int mesh_i);
void		init_values(t_aabb *left_bbox, t_aabb *right_bbox,
				unsigned int *left_count, unsigned int *right_count);
int			init_bvh(t_scene *scene);
float		calc_sah(t_scene *scene, t_bvh_node *node, int axis,
				float split_pos);
int			subdivide_bvh(unsigned int i, t_scene *scene,
				unsigned int max_nodes);
int			calc_best_axis(t_bvh_node *node, t_scene *scene,
				float *split_pos, float parent_cost);
void		init_calc_best_axis(t_vec2 *cost, int *axis);
int			add_children(unsigned int i, t_scene *scene, int best_axis,
				float split_pos);
int			set_root_bvh(t_scene *scene);

#endif // SCENE_H
