/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setenv.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jans <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 12:48:52 by jans              #+#    #+#             */
/*   Updated: 2025/01/07 11:47:04 by jsekne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	valid_arg(char *arg)
{
	char	**var;

	var = ft_split(arg, '=');
	if (!var)
		return (0);
	if (!is_valid_identifier(var[0]))
		return (ft_free_split(var), 0);
	return (ft_free_split(var), 1);
}

void	*get_val_by_key(t_dyn_arr *arr, char *str)
{
	size_t	i;
	size_t	key_len;

	key_len = ft_strlen(str);
	i = -1;
	while (++i < arr->curr_size - 1)
	{
		if (*(char **)get_val(arr, i) && !ft_strncmp(*(char **)get_val(arr, i),
				str, key_len))
			return (*(char **)get_val(arr, i));
	}
	return (NULL);
}

int	get_index(t_dyn_arr *arr, char *str)
{
	size_t	i;
	size_t	key_len;

	key_len = ft_strlen(str);
	i = -1;
	while (++i < arr->curr_size - 1)
	{
		if (*(char **)get_val(arr, i) && !ft_strncmp(*(char **)get_val(arr, i),
				str, key_len))
			return (i);
	}
	return (-1);
}
