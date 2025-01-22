/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard_expansion_utils.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsekne <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 13:55:23 by jsekne            #+#    #+#             */
/*   Updated: 2025/01/09 14:16:37 by jsekne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*join_paths(char *path, char *entry_name)
{
	char	*tmp;
	char	*full_entry;

	tmp = ft_strjoin(path, "/");
	if (!tmp)
		return (NULL);
	full_entry = ft_strjoin(tmp, entry_name);
	free(tmp);
	return (full_entry);
}

char	*append_result(char *result, char *full_entry)
{
	char	*tmp;
	char	*new_result;

	if (result)
	{
		tmp = ft_strjoin(result, " ");
		if (!tmp)
			return (NULL);
		new_result = ft_strjoin(tmp, full_entry);
		free(tmp);
		free(result);
	}
	else
	{
		new_result = ft_strdup(full_entry);
	}
	return (new_result);
}

char	*process_directory_entries(DIR *dir, char *path, char *wildcard)
{
	struct dirent	*entry;
	char			*result;
	char			*full_entry;

	result = NULL;
	entry = readdir(dir);
	while (entry != NULL)
	{
		if (wildcard_match(wildcard, entry->d_name))
		{
			full_entry = join_paths(path, entry->d_name);
			if (!full_entry)
				return (free(result), NULL);
			result = append_result(result, full_entry);
			free(full_entry);
			if (!result)
				return (NULL);
		}
		entry = readdir(dir);
	}
	return (result);
}

int	wildcard_match(const char *pattern, const char *str)
{
	if (*pattern == '\0' && *str == '\0')
		return (1);
	if (*pattern == '*' && *(pattern + 1) == '\0')
		return (1);
	if (*pattern == '*')
	{
		while (*str)
		{
			if (wildcard_match(pattern + 1, str))
				return (1);
			str++;
		}
		return (wildcard_match(pattern + 1, str));
	}
	if (*pattern == *str)
		return (wildcard_match(pattern + 1, str + 1));
	return (0);
}
