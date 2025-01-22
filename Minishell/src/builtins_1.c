/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmol <fmol@student.s19.be>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 11:07:38 by jsekne            #+#    #+#             */
/*   Updated: 2025/01/15 12:18:50 by jsekne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	exec_cd(void *arg)
{
	if (!((char **)arg)[1])
		return (0);
	if (chdir(((char **)arg)[1]) != 0)
		return (1);
	return (0);
}

int	exec_pwd(void)
{
	char	cwd[100];

	if (getcwd(cwd, sizeof(cwd)))
	{
		printf("%s\n", cwd);
		return (0);
	}
	else
		return (1);
}

int	exec_echo(void *arg)
{
	int	status;
	int	i;
	int	newline;

	i = 1;
	status = 0;
	newline = 1;
	if (!((char **)arg)[i])
		return (printf("\n"), 0);
	if (!ft_strcmp(((char **)arg)[i], "-n"))
	{
		i++;
		newline = 0;
	}
	print_echo((char **)arg, newline, i);
	if (newline)
		printf("\n");
	return (status);
}

int	exec_export(t_context *context, void *arg)
{
	size_t	i;

	i = -1;
	if (!((char **)arg)[1])
	{
		while (++i < context->envp->curr_size - 1)
			printf("declare -x  %s\n", *(char **)get_val(context->envp, i));
	}
	else
	{
		++i;
		while (((char **)arg)[++i])
		{
			if (!valid_arg(((char **)arg)[i]))
				return (printf("export: `%s': not a valid identifier\n",
						((char **)arg)[i]), 1);
			if (!ft_setenv(((char **)arg)[i], context))
				return (1);
		}
	}
	return (0);
}

int	exec_unset(t_dyn_arr *envp, void *arg)
{
	size_t	i;
	char	*front;
	char	*tmp;

	if (!((char **)arg)[1])
		return (0);
	i = find_env_var(envp, ((char **)arg)[1]);
	if (i == (size_t)-1)
		return (0);
	if (envp->curr_size == 1)
		return (replace(envp, NULL, 0, free), 0);
	tmp = *(char **)get_val(envp, i);
	front = *((char **)pop_front(envp));
	if (!front)
		return (1);
	else if (ft_strcmp(front, tmp) == 0)
		return (free(front), 0);
	return (replace(envp, &front, i - 1, free), 0);
}
