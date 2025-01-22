/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jans <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 00:59:56 by jans              #+#    #+#             */
/*   Updated: 2024/12/30 14:42:05 by jans             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	find_env_var(t_dyn_arr *envp, char *arg)
{
	size_t	i;
	size_t	len;
	char	*val;

	len = ft_strlen(arg);
	i = 0;
	while (i < envp->curr_size - 1)
	{
		val = *(char **)get_val(envp, i);
		if (ft_strncmp(val, arg, len) == 0
			&& (val[len] == '='
				|| val[len] == '\0'))
		{
			return (i);
		}
		i++;
	}
	return (-1);
}

void	print_echo(char **arg, int newline, int i)
{
	int	j;

	while (arg[i])
	{
		j = 0;
		if (i > 2 - newline)
			printf(" ");
		while (arg[i][j])
		{
			printf("%c", arg[i][j]);
			j++;
		}
		i++;
	}
}
