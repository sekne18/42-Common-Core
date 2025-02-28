/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_texture.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmol <fmol@student.s19.be>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 09:00:51 by fmol              #+#    #+#             */
/*   Updated: 2025/02/12 10:00:30 by fmol             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "loader.h"

static int	parse_ppm_header(FILE *file, int *width, int *height)
{
	char	line[MAX_LINE_LENGTH];
	char	*tmp;

	if (!fgets(line, MAX_LINE_LENGTH, file) || ft_strncmp(line, "P6\n", 3))
		return (0);
	if (!fgets(line, MAX_LINE_LENGTH, file))
		return (0);
	tmp = ft_strchr(line, ' ');
	*tmp = '\0';
	*width = ft_atoi(line);
	*height = ft_atoi(tmp + 1);
	if (*width <= 0 || *height <= 0)
		return (0);
	if (!fgets(line, MAX_LINE_LENGTH, file) || ft_strncmp(line, "255\n", 4))
		return (0);
	return (1);
}

unsigned char	*load_ppm(char *filename, int *width, int *height)
{
	FILE			*file;
	unsigned char	*data;

	file = fopen(filename, "r");
	if (!file)
		return (NULL);
	if (!parse_ppm_header(file, width, height))
		return (fclose(file), NULL);
	data = malloc(sizeof(unsigned char) * (*width * *height * 3));
	if (!data || fread(data, 1, *width * *height * 3,
			file) != (unsigned int)(*width * *height * 3))
		return (fclose(file), free(data), NULL);
	fclose(file);
	return (data);
}
