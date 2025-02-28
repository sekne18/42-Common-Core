/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   material.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmol <fmol@student.s19.be>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 14:06:34 by fmol              #+#    #+#             */
/*   Updated: 2025/02/17 16:08:09 by fmol             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scene.h"

void	destroy_texture(t_texture *texture)
{
	if (!texture)
		return ;
	if (texture->type == T_IMAGE || texture->type == T_BUMP)
	{
		free(((t_txt_img *)texture->data)->data);
		free(texture->data);
	}
	else if (texture->type == T_CHECKERBOARD)
		free(texture->data);
	else if (texture->type == T_IMG_AND_BUMP)
	{
		free(((t_txt_img *)texture->data)->data);
		free(((t_txt_img *)texture->data + 1)->data);
		free(texture->data);
	}
	free(texture);
}
