/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_token.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmol <fmol@student.s19.be>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 14:21:56 by fmol              #+#    #+#             */
/*   Updated: 2025/01/14 15:29:03 by fmol             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_token(t_token *token, int type, const char *attr, size_t attr_len)
{
	token->type = type;
	token->attr = attr;
	token->attr_len = attr_len;
	token->flags = 0;
}

int	add_word_token(const char *start, const char *curr, int flags,
		t_lexer *lexer)
{
	t_token	token;
	int		type;

	type = IDENTIFIER;
	init_token(&token, type, start, curr - start);
	token.flags |= flags;
	if (!push_back(lexer->list, &token))
		return (set_lexer_err(lexer, DYN_ARR_ERR), 0);
	return (1);
}

int	add_symbol_token(int type, const char *start, const char *curr,
		t_lexer *lexer)
{
	t_token	token;

	init_token(&token, type, start, curr - start);
	if (!push_back(lexer->list, &token))
		return (set_lexer_err(lexer, DYN_ARR_ERR), 0);
	return (1);
}
