/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save_render.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmol <fmol@student.s19.be>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/26 16:26:01 by fmol              #+#    #+#             */
/*   Updated: 2025/01/28 19:02:15 by fmol             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"
#include <fcntl.h>

void	append_color(char *buf, size_t *i, int color)
{
	if ((color >> 16 & 0xFF) > 99)
		buf[(*i)++] = ((color >> 16) & 0xFF) / 100 + '0';
	if ((color >> 16 & 0xFF) > 9)
		buf[(*i)++] = (((color >> 16) & 0xFF) / 10) % 10 + '0';
	buf[(*i)++] = ((color >> 16) & 0xFF) % 10 + '0';
	buf[(*i)++] = ' ';
	if ((color >> 8 & 0xFF) > 99)
		buf[(*i)++] = ((color >> 8) & 0xFF) / 100 + '0';
	if ((color >> 8 & 0xFF) > 9)
		buf[(*i)++] = (((color >> 8) & 0xFF) / 10) % 10 + '0';
	buf[(*i)++] = ((color >> 8) & 0xFF) % 10 + '0';
	buf[(*i)++] = ' ';
	if ((color & 0xFF) > 99)
		buf[(*i)++] = (color & 0xFF) / 100 + '0';
	if ((color & 0xFF) > 9)
		buf[(*i)++] = ((color & 0xFF) / 10) % 10 + '0';
	buf[(*i)++] = (color & 0xFF) % 10 + '0';
	buf[(*i)++] = '\n';
}

static void	process_pixel_row(t_pixel_data *data, int i)
{
	int	j;
	int	color;

	j = 0;
	while (j < data->window->img[0]->width)
	{
		color = *(int *)(data->window->img[0]->addr + (i
					* data->window->img[0]->line_length + j
					* (data->window->img[0]->bits_per_pixel / 8)));
		if (SAVE_BUFFER_SIZE - *(data->k) < 12)
		{
			write(data->fd, data->buffer, *(data->k));
			*(data->k) = 0;
		}
		append_color(data->buffer, data->k, color);
		j++;
	}
}

int	save_pixels(t_window *window, int fd)
{
	int				i;
	size_t			k;
	char			*buffer;
	t_pixel_data	data;

	buffer = malloc(SAVE_BUFFER_SIZE);
	if (!buffer)
		return (ft_putendl_fd("failed to allocate buffer", 2), 0);
	i = 0;
	k = 0;
	data = (t_pixel_data){window, buffer, &k, fd};
	while (i < window->img[0]->height)
	{
		process_pixel_row(&data, i);
		i++;
	}
	if (k > 0)
		write(fd, buffer, k);
	free(buffer);
	return (1);
}

int	save_render(t_window *window, char *filename)
{
	int	fd;

	if (!filename || ft_strlen(filename) <= 4 || ft_strncmp(filename
			+ ft_strlen(filename) - 4, ".ppm", 4))
		return (ft_putendl_fd("Invalid filename. Must end with .ppm", 2), 1);
	fd = open(filename, O_CREAT | O_WRONLY, 0644);
	if (fd < 0)
		return (ft_putendl_fd("failed to open file", 2), 1);
	write(fd, "P3\n", 3);
	ft_putnbr_fd(window->img[0]->width, fd);
	ft_putchar_fd(' ', fd);
	ft_putnbr_fd(window->img[0]->height, fd);
	ft_putchar_fd('\n', fd);
	ft_putnbr_fd(255, fd);
	ft_putchar_fd('\n', fd);
	if (!save_pixels(window, fd))
	{
		close(fd);
		return (1);
	}
	close(fd);
	return (0);
}
