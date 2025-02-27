/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytrace.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmol <fmol@student.s19.be>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 11:41:37 by fmol              #+#    #+#             */
/*   Updated: 2025/02/18 14:32:00 by fmol             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raytracer.h"
#include "scene.h"

t_hit_record	get_hit(t_ray *ray, t_scene *scene)
{
	t_hit_record	record;
	float			t;
	unsigned int	i;

	ft_memset(&record, 0, sizeof(t_hit_record));
	record.t = FLT_MAX;
	intersect_bvh(ray, scene, &record);
	i = scene->object_count - scene->plane_count;
	while (i < scene->object_count)
	{
		t = check_hit(ray, &scene->objects[i]);
		if (t > 0.0 && t < record.t)
			fill_record(&record, ray, &scene->objects[i], t);
		i++;
	}
	return (record);
}

void	set_atmosphere_color(t_vec3 *colors, t_material *material,
	t_scene *scene, t_vec3 *orig_ray_dir)
{
	t_vec3	atmosphere;

	atmosphere = lerp_vec_multiple(scene->amb_light,
			scene->amb_light_count, 0.5 * (orig_ray_dir->y + 1.0));
	if (material)
		mul_local(&atmosphere, &material->ambient);
	add_local(colors + 1, mul_local(colors, &atmosphere));
}

void	set_color(t_hit_record *record, t_vec3 *colors,
	t_ray *ray, unsigned int *seed)
{
	t_vec3	emitted_light;
	t_vec3	tmp;
	float	specular_bounce;

	specular_bounce = set_bounce_ray_dir(ray, record, seed);
	if (specular_bounce > 0.0)
		specular_bounce = 1.0;
	add_scaled_local(&ray->origin, &ray->direction, 0.00001);
	mul_scalar(&emitted_light, &record->material->emission,
		record->material->emission_intensity);
	copy_vector(&tmp, colors);
	add_local(colors + 1, mul_local(&tmp, &emitted_light));
	tmp = get_texture_color(record->material,
			&record->uv, &record->point, record->type);
	tmp = lerp_vec(&tmp, &record->material->specular, specular_bounce);
	mul_local(colors, &tmp);
}

t_vec3	pathtrace(t_ray ray, t_scene *scene, unsigned int *seed)
{
	t_vec3			colors[2];
	size_t			i;
	t_hit_record	record;
	t_material		*last_material;
	t_vec3			orig_ray_dir;

	last_material = NULL;
	copy_vector(&orig_ray_dir, &ray.direction);
	set_vector(colors, 1.0, 1.0, 1.0);
	set_vector(colors + 1, 0.0, 0.0, 0.0);
	i = 0;
	while (i++ < MAX_BOUNCES + 1)
	{
		record = get_hit(&ray, scene);
		if (!record.hit)
		{
			set_atmosphere_color(colors, last_material, scene, &orig_ray_dir);
			break ;
		}
		last_material = record.material;
		ray.origin = record.point;
		adjust_texture_normal(&record);
		set_color(&record, colors, &ray, seed);
	}
	return (colors[1]);
}
