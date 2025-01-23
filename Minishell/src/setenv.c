/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setenv.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmol <fmol@student.s19.be>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 12:48:52 by jans              #+#    #+#             */
/*   Updated: 2025/01/15 10:28:21 by fmol             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_setenv(char *arg, t_context *ctx)
{
	char	*env_var;
	char	**var;
	char	*value;
	char	*tmp_key;

	var = ft_split(arg, '=');
	if (!var)
		return (0);
	env_var = (char *)get_val_by_key(ctx->envp, var[0]);
	if (!env_var)
	{
		tmp_key = ft_strdup(arg);
		if (!insert_new_env(tmp_key, ctx->envp))
			return (ft_free_split(var), 1);
	}
	else
	{
		tmp_key = ft_strdup(var[0]);
		value = ft_strdup(arg);
		if (!set_env_value(tmp_key, value, ctx->envp))
			return (ft_free_split(var), free(tmp_key), 1);
		free(value);
	}
	return (ft_free_split(var), free(tmp_key), 0);
}

int	set_env_value(char *key, char *new_value, t_dyn_arr *envp)
{
	int	idx;

	idx = get_index(envp, key);
	if (idx == -1)
		return (1);
	replace(envp, &new_value, idx, free);
	return (0);
}

int	insert_new_env(char *value, t_dyn_arr *envp)
{
	replace(envp, &value, envp->curr_size - 1, free);
	if (!push_back(envp, NULL))
		return (DYN_ARR_ERR);
	return (0);
}
