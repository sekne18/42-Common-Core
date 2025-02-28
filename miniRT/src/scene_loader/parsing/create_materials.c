/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_materials.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmol <fmol@student.s19.be>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 18:40:43 by jans              #+#    #+#             */
/*   Updated: 2025/02/13 13:58:50 by fmol             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

/*
 * PARAMETERS: context, line
 * DESCRIPTION: Creates materials from the line.
 * RETURNS: 1 if the values are valid, 0 if the values are invalid.
 * */
int	build_materials(t_context *context, char *line, t_list *mtl_ids)
{
	char	**split;

	split = ft_split(line, ' ');
	if (!split)
		return (ERR_MEM);
	if (!ft_strncmp(split[0], "mtl", 3))
	{
		if (!build_material(context, split, mtl_ids))
			return (ft_free_split(split), 0);
	}
	return (ft_free_split(split), 1);
}

int	build_texture(t_material *mat, t_texture_type type, char **values)
{
	t_texture	*texture;
	t_vec3		colors[2];

	if (type == T_CHECKERBOARD)
	{
		colors[0] = get_remapped_color(values[11]);
		colors[1] = get_remapped_color(values[12]);
		texture = create_checkerboard_texture(colors, colors + 1);
	}
	else if (type == T_IMAGE)
		texture = create_img_texture(values[11]);
	else if (type == T_BUMP)
		texture = create_bump_texture(values[11]);
	else if (type == T_IMG_AND_BUMP)
		texture = create_img_bump_texture(values[11], values[12]);
	else
	{
		mat->texture = NULL;
		return (1);
	}
	if (!texture)
		return (0);
	mat->texture = texture;
	return (1);
}

t_texture_type	determine_txt_type(char *txt_type)
{
	if (!ft_strcmp(txt_type, "CHECKER"))
		return (T_CHECKERBOARD);
	else if (!ft_strcmp(txt_type, "TXT"))
		return (T_IMAGE);
	else if (!ft_strcmp(txt_type, "BUMP"))
		return (T_BUMP);
	else if (!ft_strcmp(txt_type, "TXT_BUMP"))
		return (T_IMG_AND_BUMP);
	return (T_NONE);
}

/*
 * PARAMETERS: context, values
 * DESCRIPTION: Creates a material from the values.
 * RETURNS: 1 if the values are valid, 0 if the values are invalid.
 * */
int	build_material(t_context *context, char **values, t_list *mtl_ids)
{
	t_material	material;

	material.ambient = get_remapped_color(values[1]);
	material.diffuse = get_remapped_color(values[2]);
	material.specular = get_remapped_color(values[3]);
	material.emission = get_remapped_color(values[4]);
	material.emission_intensity = ft_atof(values[5]);
	material.smoothness = ft_atof(values[6]);
	material.specular_intensity = ft_atof(values[7]);
	material.refraction_intensity = ft_atof(values[8]);
	material.refractive_index = ft_atof(values[9]);
	if (!build_texture(&material, determine_txt_type(values[10]), values))
		return (0);
	context->scene->materials[get_mtl_index(values[0], mtl_ids)] = material;
	return (1);
}

/*
 * PARAMETERS: name
 * DESCRIPTION: Gets the index of the material from the name.
 * RETURNS: index of the material
 * */
int	get_mtl_index(char *name, t_list *mtl_ids)
{
	t_list	*head;
	char	*tmp;
	int		i;

	i = 0;
	head = mtl_ids;
	tmp = ft_strdup(name);
	while (head)
	{
		if (ft_strcmp(head->content, tmp) == 0)
			break ;
		head = head->next;
		i++;
	}
	return (free(tmp), i);
}
