/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_util.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmol <fmol@student.s19.be>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 16:16:09 by jsekne            #+#    #+#             */
/*   Updated: 2025/01/15 10:21:57 by fmol             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*get_path(char *envp[])
{
	size_t	i;

	i = 0;
	while (envp[i] && ft_strncmp(envp[i], "PATH=", 5))
		i++;
	if (!envp[i])
		return (NULL);
	return (envp[i] + 5);
}

static char	*path_join(char *path, char *file)
{
	size_t	l_1;
	size_t	l_2;
	size_t	i;
	char	*res;

	l_1 = ft_strlen(path);
	l_2 = ft_strlen(file);
	res = malloc(sizeof(char) * (2 + l_1 + l_2));
	if (!res)
		return (NULL);
	res[l_1 + l_2 + 1] = 0;
	i = -1;
	while (++i < l_1)
		res[i] = path[i];
	res[i] = '/';
	i = -1;
	while (++i < l_2)
		res[l_1 + 1 + i] = file[i];
	return (res);
}

static char	*find_cmd(char *cmd, char *envp[])
{
	size_t	i;
	char	**dirs;
	char	*full_path;

	full_path = get_path(envp);
	if (!full_path)
		return (NULL);
	dirs = ft_split(full_path, ':');
	if (!dirs)
		return (NULL);
	i = 0;
	while (dirs[i])
	{
		full_path = path_join(dirs[i], cmd);
		if (!full_path)
			return (ft_free_split(dirs), NULL);
		else if (!access(full_path, X_OK))
			return (ft_free_split(dirs), full_path);
		free(full_path);
		i++;
	}
	return (ft_free_split(dirs), NULL);
}

int	add_path(char **cmd, char *envp[])
{
	char	*full;

	if (!cmd || !*cmd || **cmd == '\0')
		return (0);
	if (!access(*cmd, X_OK))
		return (1);
	full = find_cmd(*cmd, envp);
	if (!full)
		return (0);
	*cmd = full;
	return (1);
}
