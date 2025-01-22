/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_arg.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmol <fmol@student.s19.be>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 15:31:03 by fmol              #+#    #+#             */
/*   Updated: 2025/01/14 14:18:47 by fmol             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	add_expanded_args(t_dyn_arr *args, char *arg)
{
	char	**tmp_split;
	int		i;

	i = -1;
	arg = expand_wildcard(arg);
	tmp_split = ft_split(arg, ' ');
	if (!tmp_split)
		return (MALLOC_ERR);
	free(arg);
	while (tmp_split[++i])
	{
		if (!push_back(args, &tmp_split[i]))
			return (free(tmp_split), DYN_ARR_ERR);
	}
	return (free(tmp_split), 0);
}

int	exec_args(void *data, t_context *ctx)
{
	t_token	*token;
	char	*arg;

	token = (t_token *)data;
	(void)ctx;
	arg = expand_token(token, ctx);
	if (!arg)
		return (MALLOC_ERR);
	if (ctx->args->curr_size == 0 && !push_back(ctx->args, NULL))
		return (free(arg), DYN_ARR_ERR);
	if (token->flags & WILDCARD)
		return (add_expanded_args(ctx->args, arg));
	else
	{
		if (!push_back(ctx->args, &arg))
			return (free(arg), DYN_ARR_ERR);
	}
	return (0);
}
