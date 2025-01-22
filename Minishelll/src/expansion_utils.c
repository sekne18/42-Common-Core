/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsekne <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 13:55:23 by jsekne            #+#    #+#             */
/*   Updated: 2025/01/09 13:55:33 by jsekne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*finalize_expansion(char *res, const char *curr, t_token *token)
{
	char	*tmp;
	char	*tmp_dup;

	if (curr >= token->attr + token->attr_len)
		return (res);
	tmp_dup = ft_strndup(curr, token->attr + token->attr_len - curr);
	tmp = ft_strjoin(res, tmp_dup);
	free(tmp_dup);
	free(res);
	return (tmp);
}

char	*append_to_result(char *res, t_token *token, const char *curr,
		char *var)
{
	char	*tmp;
	char	*tmp_dup;

	if (!res)
		res = ft_strndup(token->attr, var - token->attr);
	else
	{
		tmp_dup = ft_strndup(curr, var - curr);
		tmp = ft_strjoin(res, tmp_dup);
		free(res);
		free(tmp_dup);
		res = tmp;
	}
	return (res);
}

char	*append_var_to_result(char *res, char *var)
{
	char	*tmp;

	tmp = ft_strjoin(res, var);
	free(res);
	free(var);
	return (tmp);
}

void	consume_var_chars(const char **var, size_t	i)
{
	while (is_var_char(**var, i++))
		(*var)++;
}
