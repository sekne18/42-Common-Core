/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmol <fmol@student.s19.be>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 10:00:39 by jans              #+#    #+#             */
/*   Updated: 2025/02/18 15:08:27 by fmol             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include "scene.h"
# include "vector.h"
# include <fcntl.h>
# include "libft.h"

// Error codes
# define ERR_FILE 11
# define ERR_NO_INIT 10
# define ERR_NO_OBJ 9
# define ERR_INV_ORDER 8
# define ERR_NO_MTL 7
# define ERR_MEM 6
# define ERR_DUP_INIT 5
# define ERR_INV_TYPE 4
# define ERR_INV_LINE 3
# define ERR_DUP_MTL 2
# define SUCCESS 1

typedef enum e_parse_type
{
	P_MATERIAL,
	P_OBJECT,
	P_MESH,
	P_CAMERA,
	P_AMB_LIGHT,
	P_WINDOW,
	P_PLANE,
}	t_parse_type;

typedef struct s_obj_count
{
	int		mat_count;
	int		obj_count;
	int		mesh_count;
	int		plane_count;
	int		window_init;
	int		amb_light_init;
	int		cam_init;
	int		obj_i;
	int		mesh_i;
	int		plane_i;
}	t_obj_count;

t_parse_type	parse_type(char *line);
void			set_obj_count(t_obj_count *obj_counts);
int				inc_obj_count(char *line, t_obj_count *obj_counts);
int				contains_duplicate_ids(t_list *mtl_ids);
int				save_material_id(char *line, t_list **mtl_ids);
int				valid_coordinates(char *value);
int				valid_quat(char *value);
int				valid_rgb(char *value);
int				valid_material(char **values);
int				valid_camera(char **values);
int				valid_window(char **values);
int				valid_amb_light(char **values);
int				valid_object(char **values, t_list *mtl_ids);
int				valid_line(t_parse_type type, char *line, t_list *mtl_ids);

int				valid_cylinder(char **values, t_list *mtl_ids);
int				valid_disk(char **values, t_list *mtl_ids);
int				valid_triangle(char **values, t_list *mtl_ids);
int				valid_sphere(char **values, t_list *mtl_ids);
int				valid_plane(char **values, t_list *mtl_ids);
int				valid_square(char **values, t_list *mtl_ids);
int				valid_mesh(char **values, t_list *mtl_ids);

int				valid_material_id(char *value, t_list *mtl_ids);
int				valid_normalized_vec(char *value);
int				valid_rgb_value(char *value);

int				ft_split_size(char **split);
int				ft_isfloat(char *str);
float			ft_atof(char *str);
int				ft_isnumber(char *str);
t_material		*get_material(char *name, t_material *materials,
					t_list *mtl_ids);
t_vec3			get_vec3(char *coordinates);
t_quat			get_quat(char *coordinates);
t_vec3			get_remapped_color(char *color);
t_vec3			remap_color(t_vec3 vec);
t_object		build_object(t_object_type type, void *data,
					t_material *material);
int				get_mtl_index(char *name, t_list *mtl_ids);
int				calc_obj_i(t_obj_count *count);
int				calc_plane_i(t_obj_count *count);
int				determine_object_type(char *line);

void			handle_error_message(int status_code);

#endif // PARSING_H