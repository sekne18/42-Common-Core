/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   obj_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmol <fmol@student.s19.be>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 15:52:19 by jans              #+#    #+#             */
/*   Updated: 2025/02/17 11:36:31 by fmol             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

int	calc_obj_i(t_obj_count *count)
{
	return (count->obj_i + count->mesh_count);
}

int	calc_plane_i(t_obj_count *count)
{
	return (count->obj_count + count->mesh_count + count->plane_i);
}

t_parse_type	parse_type(char *line)
{
	if (!ft_strncmp(line, "mtl", 3))
		return (P_MATERIAL);
	else if (!ft_strncmp(line, "A ", 2))
		return (P_AMB_LIGHT);
	else if (!ft_strncmp(line, "C ", 2))
		return (P_CAMERA);
	else if (!ft_strncmp(line, "W ", 2))
		return (P_WINDOW);
	else if (!ft_strncmp(line, "sp ", 3) || !ft_strncmp(line, "cy ", 3)
		|| !ft_strncmp(line, "sq ", 3) || !ft_strncmp(line, "tr ", 3)
		|| !ft_strncmp(line, "ds ", 3))
		return (P_OBJECT);
	else if (!ft_strncmp(line, "pl ", 3))
		return (P_PLANE);
	else if (!ft_strncmp(line, "obj ", 4))
		return (P_MESH);
	return (0);
}
