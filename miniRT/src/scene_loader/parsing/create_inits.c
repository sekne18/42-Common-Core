/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_inits.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmol <fmol@student.s19.be>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 10:48:13 by fmol              #+#    #+#             */
/*   Updated: 2025/02/13 16:57:43 by fmol             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

int	build_camera(t_context *c, char *line)
{
	char	**values;
	t_vec3	origin;
	t_vec3	normal;
	float	fov;

	values = ft_split(line, ' ');
	if (!values || ft_split_size(values) != 4)
		return (ft_free_split(values), 0);
	origin = get_vec3(values[1]);
	normal = get_vec3(values[2]);
	normalize_local(&normal);
	fov = ft_atof(values[3]);
	if (fov < 0 || fov > 180)
		return (ft_free_split(values), 0);
	ft_free_split(values);
	if (!init_camera(c, origin, normal, to_radians(fov)))
		return (0);
	return (1);
}

int	build_amb_light(t_context *c, char *line)
{
	char			**values;
	unsigned int	i;
	unsigned int	arr_size;
	t_vec3			*colors;
	float			ratio;

	values = ft_split(line, ' ');
	if (!values)
		return (0);
	ratio = ft_atof(values[1]);
	(void)ratio;
	arr_size = ft_atoi(values[2]);
	colors = malloc(sizeof(t_vec3) * arr_size);
	if (!colors)
		return (ft_free_split(values), 0);
	i = 0;
	while (i < arr_size)
	{
		colors[i] = get_remapped_color(values[3 + i]);
		i++;
	}
	ft_free_split(values);
	c->scene->amb_light = colors;
	c->scene->amb_light_count = arr_size;
	return (1);
}

int	build_window(t_context *c, char *line)
{
	char	**values;
	int		width;
	int		height;

	values = ft_split(line, ' ');
	if (!values || ft_split_size(values) != 3)
		return (ft_free_split(values), 0);
	width = ft_atoi(values[1]);
	height = ft_atoi(values[2]);
	ft_free_split(values);
	c->width = width;
	c->height = height;
	return (1);
}

/*
 * PARAMETERS: object type, object data, material
 * DESCRIPTION: Builds an object with the given parameters.
 * RETURNS: t_object
 * */
t_object	build_object(t_object_type type, void *data, t_material *material)
{
	t_object	object;

	object.type = type;
	object.data = data;
	object.material = material;
	return (object);
}
