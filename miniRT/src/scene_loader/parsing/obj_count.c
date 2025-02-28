/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   obj_count.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmol <fmol@student.s19.be>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 19:30:55 by jans              #+#    #+#             */
/*   Updated: 2025/02/13 14:10:25 by fmol             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

static int	inc_obj_counts(int type, t_obj_count *obj_counts)
{
	if (type == P_MATERIAL)
	{
		if ((obj_counts->obj_count + obj_counts->plane_count
				+ obj_counts->mesh_count) > 0)
			return (ERR_INV_ORDER);
		obj_counts->mat_count++;
	}
	else if (type == P_OBJECT)
		obj_counts->obj_count++;
	else if (type == P_PLANE)
		obj_counts->plane_count++;
	else if (type == P_MESH)
		obj_counts->mesh_count++;
	else if (type == P_CAMERA)
		obj_counts->cam_init++;
	else if (type == P_AMB_LIGHT)
		obj_counts->amb_light_init++;
	else if (type == P_WINDOW)
		obj_counts->window_init++;
	return (SUCCESS);
}

static int	is_object(int type)
{
	return (type == P_OBJECT || type == P_PLANE || type == P_MESH);
}

int	inc_obj_count(char *line, t_obj_count *obj_counts)
{
	int	ret;
	int	type;

	type = parse_type(line);
	if ((type != P_AMB_LIGHT && type != P_CAMERA && type != P_WINDOW
			&& type != P_MATERIAL && type != P_OBJECT && type != P_PLANE
			&& type != P_MESH))
		return (ERR_INV_TYPE);
	if (!obj_counts->mat_count && is_object(type))
		return (ERR_NO_MTL);
	if (type == P_WINDOW && obj_counts->cam_init)
		return (ERR_INV_ORDER);
	ret = inc_obj_counts(type, obj_counts);
	if (ret != SUCCESS)
		return (ret);
	if (obj_counts->cam_init > 1 || obj_counts->amb_light_init > 1
		|| obj_counts->window_init > 1)
		return (ERR_DUP_INIT);
	return (SUCCESS);
}

void	set_obj_count(t_obj_count *obj_counts)
{
	ft_memset(obj_counts, 0, sizeof(t_obj_count));
}
