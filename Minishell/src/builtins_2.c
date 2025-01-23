/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmol <fmol@student.s19.be>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 11:08:01 by jsekne            #+#    #+#             */
/*   Updated: 2025/01/15 10:22:50 by fmol             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	exec_cat(char *path)
{
	(void)path;
	return (0);
}

int	exec_env(char **envp, char *arg)
{
	char	**env;

	env = envp;
	if (arg != NULL)
		return (ft_putendl_fd("minishell: env: Arguments not expected.",
				STDERR_FILENO), 1);
	while (*env != NULL)
	{
		printf("%s\n", *env);
		env++;
	}
	return (0);
}

int	get_status(char **arg)
{
	int		status;
	int		i;
	char	*tmp;

	i = -1;
	if (arg[1] == NULL)
		return (0);
	if (arg[2] != NULL)
	{
		ft_putendl_fd("minishell: exit: too many arguments", STDERR_FILENO);
		return (0);
	}
	tmp = arg[1];
	if (tmp[0] == '-')
		i++;
	while (tmp[++i])
	{
		if (ft_isdigit(tmp[i]) == 0)
			return (2);
	}	
	status = ft_atoi(tmp);
	if (status < 0)
		status = (256 + status) % 256;
	else if (status > 255)
		status = status % 256;
	return (status);
}
