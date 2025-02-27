/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   img_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmol <fmol@student.s19.be>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 15:55:06 by fmol              #+#    #+#             */
/*   Updated: 2025/02/19 10:03:30 by fmol             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

void	copy_img(t_img *dest, t_img *src)
{
	if (!dest || !src || dest->width != src->width
		|| dest->height != src->height)
		return ;
	ft_memcpy(dest->addr, src->addr, src->line_length * src->height);
}

//remove false from conditionals to get overexposed image
void	avg_img(t_img *acc, t_img *new, int frame_nr)
{
	int		i;
	float	alpha;
	t_vec3	color;
	t_vec3	tmp;

	alpha = 1.0 / (frame_nr + 1);
	i = 0;
	while (i < acc->width * acc->height)
	{
		color = int_to_vec3(((unsigned int *)acc->addr)[i]);
		tmp = int_to_vec3(((unsigned int *)new->addr)[i]);
		if (color.x == 0 && color.y == 0 && color.z == 0 && 0)
			color = tmp;
		else if (tmp.x == 0 && tmp.y == 0 && tmp.z == 0 && 0)
			;
		else
		{
			mul_scalar_local(&color, 1.0 - alpha);
			mul_scalar_local(&tmp, alpha);
			add_local(&color, &tmp);
		}
		my_mlx_pixel_put(acc, i % acc->width, i / acc->width,
			vec3_to_int(&color));
		i++;
	}
}

void	my_mlx_pixel_put(t_img *img, int x, int y, int color)
{
	char	*dst;

	if (x < 0 || y < 0 || x >= img->width || y >= img->height)
		return ;
	dst = img->addr + (y * img->line_length + x * (img->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

void	clear_img(t_img *img)
{
	int	x;
	int	y;

	y = 0;
	while (y < img->height)
	{
		x = 0;
		while (x < img->width)
		{
			my_mlx_pixel_put(img, x, y, 0xFF000000);
			x++;
		}
		y++;
	}
}

t_img	*create_img(void *mlx_ptr, int width, int height)
{
	t_img	*ptr;

	ptr = malloc(sizeof(t_img));
	if (!ptr)
		return (NULL);
	ptr->img = mlx_new_image(mlx_ptr, width, height);
	if (!ptr->img)
	{
		free(ptr);
		return (NULL);
	}
	ptr->addr = mlx_get_data_addr(ptr->img, &ptr->bits_per_pixel,
			&ptr->line_length, &ptr->endian);
	if (!ptr->addr)
	{
		mlx_destroy_image(mlx_ptr, ptr->img);
		free(ptr);
		return (NULL);
	}
	ptr->width = width;
	ptr->height = height;
	return (ptr);
}
