/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_scene.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmol <fmol@student.s19.be>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 15:27:11 by fmol              #+#    #+#             */
/*   Updated: 2025/02/17 16:32:17 by fmol             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

int	load_scene(t_context *context, char *filename)
{
	t_obj_count	obj_counts;
	t_list		*mtl_ids;
	int			status_code;

	mtl_ids = NULL;
	context->scene = malloc(sizeof(t_scene));
	if (!context->scene)
		return (0);
	init_scene(context->scene);
	status_code = first_pass(context, filename, &obj_counts, &mtl_ids);
	if (status_code != SUCCESS)
		return (ft_lstclear(&mtl_ids, free),
			handle_error_message(status_code), status_code);
	status_code = second_pass(context, filename, mtl_ids, &obj_counts);
	if (status_code != SUCCESS)
		return (ft_lstclear(&mtl_ids, free), handle_error_message(status_code),
			status_code);
	ft_lstclear(&mtl_ids, free);
	if (!context->scene->objects || !context->scene->materials)
		return (0);
	return (1);
}

void	handle_error_message(int status_code)
{
	if (status_code == ERR_INV_ORDER)
		ft_putendl_fd("Invalid order of elements in scene file", 1);
	else if (status_code == ERR_NO_MTL)
		ft_putendl_fd("No material defined for object", 1);
	else if (status_code == ERR_MEM)
		ft_putendl_fd("Failed to allocate memory", 1);
	else if (status_code == ERR_DUP_INIT)
		ft_putendl_fd("Duplicate in the initialization", 1);
	else if (status_code == ERR_INV_LINE)
		ft_putendl_fd("Invalid type/values in scene file", 1);
	else if (status_code == ERR_INV_TYPE)
		ft_putendl_fd("Invalid type in scene file", 1);
	else if (status_code == ERR_DUP_MTL)
		ft_putendl_fd("Duplicate material id", 1);
	else if (status_code == ERR_NO_INIT)
		ft_putendl_fd("No initialization of window, \
		camera or ambient light", 1);
	else if (status_code == ERR_NO_OBJ)
		ft_putendl_fd("No objects defined in scene file", 1);
	else if (status_code == ERR_FILE)
		ft_putendl_fd("Failed to open file", 1);
	else
		ft_putendl_fd("Unknown error", 1);
}
