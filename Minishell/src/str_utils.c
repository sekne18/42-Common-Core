/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmol <fmol@student.s19.be>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 13:57:51 by jsekne            #+#    #+#             */
/*   Updated: 2025/01/15 10:28:09 by fmol             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_valid_identifier(char *key)
{
	int	i;

	i = 0;
	if (!key || !ft_isalpha(key[0]))
		return (0);
	while (key[++i])
	{
		if (!ft_isalnum(key[i]) && key[i] != '_')
			return (0);
	}
	return (1);
}

int	is_var_char(char c, size_t i)
{
	if (i == 0)
		return ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z') || c == '_');
	return ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z')
		|| c == '_' || (c >= '0' && c <= '9'));
}

char	*get_var_val(const char **var, char **envp, t_context *context)
{
	size_t	i;
	size_t	j;

	i = 0;
	(*var)++;
	if (**var == '?')
	{
		(*var)++;
		return (ft_itoa(context->last_exit_status));
	}
	while (envp[i])
	{
		j = 0;
		while (envp[i][j] && envp[i][j] == (*var)[j])
			j++;
		if (envp[i][j] == '=' && (!(*var)[j] || !is_var_char((*var)[j], j)))
		{
			*var += j;
			return (ft_strndup(envp[i] + j + 1, ft_strlen(envp[i] + j + 1)));
		}
		i++;
	}
	consume_var_chars(var, 0);
	return (ft_strdup(""));
}

char	*get_var_val_inside(char *envp, const char **var)
{
	size_t	i;

	i = 0;
	while (envp && envp[i] == (*var)[i])
		i++;
	if (envp[i] == '=' && (!(*var)[i] || !is_var_char((*var)[i], i)))
	{
		*var += i;
		return (ft_strndup(envp + i + 1, ft_strlen(envp + i + 1)));
	}
	return (NULL);
}

int	has_multiple_assigns(char *envp)
{
	int	count;

	count = 0;
	while (*envp)
	{
		if (*envp == '=')
			count++;
		envp++;
	}
	return (count > 0);
}
