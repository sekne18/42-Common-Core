/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_textures.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jans <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 09:51:03 by jans              #+#    #+#             */
/*   Updated: 2025/02/17 09:51:05 by jans             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "loader.h"

t_texture	*create_img_texture(char *filename)
{
	t_texture	*texture;
	t_txt_img	*img;

	if (!filename || ft_strlen(filename) <= 4 || ft_strncmp(filename
			+ ft_strlen(filename) - 4, ".ppm", 4))
		return (NULL);
	texture = malloc(sizeof(t_texture));
	img = malloc(sizeof(t_txt_img));
	if (!texture || !img)
		return (free(texture), free(img), NULL);
	img->data = load_ppm(filename, &img->width, &img->height);
	if (!img->data)
	{
		write(2, "failed to load texture\n", 23);
		return (free(img), free(texture), NULL);
	}
	texture->type = T_IMAGE;
	texture->data = img;
	return (texture);
}

t_texture	*create_bump_texture(char *filename)
{
	t_texture	*texture;
	t_txt_img	*img;

	if (!filename || ft_strlen(filename) <= 4 || ft_strncmp(filename
			+ ft_strlen(filename) - 4, ".ppm", 4))
		return (NULL);
	texture = malloc(sizeof(t_texture));
	img = malloc(sizeof(t_txt_img));
	if (!texture || !img)
		return (free(texture), free(img), NULL);
	img->data = load_ppm(filename, &img->width, &img->height);
	if (!img->data)
	{
		write(2, "failed to load texture\n", 23);
		return (free(img), free(texture), NULL);
	}
	texture->type = T_BUMP;
	texture->data = img;
	return (texture);
}

t_texture	*create_checkerboard_texture(t_vec3 *color1, t_vec3 *color2)
{
	t_texture	*texture;
	t_vec3		*colors;

	texture = malloc(sizeof(t_texture));
	colors = malloc(sizeof(t_vec3) * 2);
	if (!texture || !colors)
		return (free(texture), free(colors), NULL);
	texture->type = T_CHECKERBOARD;
	colors[0] = *color1;
	colors[1] = *color2;
	texture->data = colors;
	return (texture);
}

t_texture	*create_img_bump_texture(char *filename, char *bump_filename)
{
	t_texture	*texture;
	t_txt_img	*data;

	if (!filename || ft_strlen(filename) <= 4 || ft_strncmp(filename
			+ ft_strlen(filename) - 4, ".ppm", 4))
		return (NULL);
	texture = malloc(sizeof(t_texture));
	data = malloc(sizeof(t_txt_img) * 2);
	if (!texture || !data)
		return (free(texture), free(data), NULL);
	data->data = load_ppm(filename, &(data)->width, &(data)->height);
	(data + 1)->data = load_ppm(bump_filename, &(data + 1)->width, &(data
				+ 1)->height);
	if (!data->data || !(data + 1)->data)
	{
		write(2, "failed to load texture\n", 23);
		free(data->data);
		free((data + 1)->data);
		return (free(texture), free(data), NULL);
	}
	texture->type = T_IMG_AND_BUMP;
	texture->data = data;
	return (texture);
}
