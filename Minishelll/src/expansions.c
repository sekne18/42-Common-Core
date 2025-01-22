/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansions.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmol <fmol@student.s19.be>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 08:09:36 by jsekne            #+#    #+#             */
/*   Updated: 2025/01/14 09:44:47 by fmol             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*expand_token_loop(t_token *token, t_context *context)
{
	char		*var;
	char		*res;
	const char	*curr;

	curr = token->attr;
	res = NULL;
	while (curr < token->attr + token->attr_len)
	{
		var = ft_strchr(curr, '$');
		if (!var)
			return (finalize_expansion(res, curr, token));
		res = append_to_result(res, token, curr, var);
		if (!res)
			return (NULL);
		curr = var;
		var = get_var_val(&curr, context->envp->data, context);
		if (!var)
			return (free(res), NULL);
		res = append_var_to_result(res, var);
		if (!res)
			return (NULL);
	}
	return (res);
}

char	*expand_token(t_token *token, t_context *context)
{
	char	*res;

	if (token->type != IDENTIFIER)
		return (NULL);
	if (!(token->flags & HAS_VAR) || (token->flags & QUOTE))
		return (ft_strndup(token->attr, token->attr_len));
	res = expand_token_loop(token, context);
	return (res);
}

char	*get_wildcard_path(char *cmd, char **wildcard)
{
	char	*path;

	*wildcard = ft_strrchr(cmd, '/');
	if (*wildcard)
	{
		**wildcard = '\0';
		path = cmd;
		(*wildcard)++;
	}
	else
	{
		path = ".";
		*wildcard = cmd;
	}
	return (path);
}

char	*expand_wildcard(char *cmd)
{
	DIR		*dir;
	char	*result;
	char	*path;
	char	*wildcard;

	result = NULL;
	path = get_wildcard_path(cmd, &wildcard);
	dir = opendir(path);
	if (!dir)
	{
		if (wildcard != cmd)
			*(wildcard - 1) = '/';
		return (cmd);
	}
	result = process_directory_entries(dir, path, wildcard);
	closedir(dir);
	if (!result)
		return (cmd);
	free(cmd);
	return (result);
}
