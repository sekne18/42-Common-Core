/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   match_token.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmol <fmol@student.s19.be>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 14:17:42 by fmol              #+#    #+#             */
/*   Updated: 2025/01/14 15:26:23 by fmol             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	match_keywords_helper(char **start, t_lexer *lexer, char *curr,
		int flags)
{
	if (flags & QUOTE || flags & D_QUOTE)
	{
		if (((flags & QUOTE && peek(curr, '\''))
				|| (flags & D_QUOTE && peek(curr, '"'))))
		{
			if (!add_word_token(*start, curr, flags, lexer))
				return (set_lexer_err(lexer, DYN_ARR_ERR), 0);
			*start = curr + 1;
			return (1);
		}
		return (set_lexer_err(lexer, QUOTE_ERR), 0);
	}
	else if (curr - *start > 0)
	{
		if (!add_word_token(*start, curr, flags, lexer))
			return (set_lexer_err(lexer, DYN_ARR_ERR), 0);
		*start = curr;
		return (1);
	}
	return (0);
}

/*
 * cases:
 * 1) empty quotes
 * 2) identifier between quotes
 * 3) identifier without quotes
 * 4) unclosed quotes
 */
int	match_keywords(char **start, t_lexer *lexer)
{
	char	*curr;
	int		flags;

	flags = 0;
	if (match(start, '\''))
		flags |= QUOTE;
	else if (match(start, '"'))
		flags |= D_QUOTE;
	curr = *start;
	while ((flags & QUOTE && *curr == '\"')
		|| (flags & D_QUOTE && *curr == '\'')
		|| is_identifier_char(*curr, flags))
	{
		if (!(flags & QUOTE) && *curr == '$')
			flags |= HAS_VAR;
		else if (!(flags & QUOTE || flags & D_QUOTE) && *curr == '*')
			flags |= WILDCARD;
		curr++;
	}
	return (match_keywords_helper(start, lexer, curr, flags));
}

static int	match_symbols_helper(char **start, t_lexer *lexer, char *begin)
{
	if (match(start, '<'))
	{
		if (match(start, '<'))
			return (add_symbol_token(HEREDOC, begin, *start, lexer));
		else
			return (add_symbol_token(L_REDIR, begin, *start, lexer));
	}
	else if (match(start, '>'))
	{
		if (match(start, '>'))
			return (add_symbol_token(APPEND, begin, *start, lexer));
		else
			return (add_symbol_token(R_REDIR, begin, *start, lexer));
	}
	else if (peek(*start, '&') && peek(*start + 1, '&'))
	{
		*start += 2;
		return (add_symbol_token(AND, begin, *start, lexer));
	}
	return (2);
}

int	match_symbols(char **start, t_lexer *lexer)
{
	char	*begin;

	begin = *start;
	if (match_symbols_helper(start, lexer, begin) == 1)
		return (1);
	else if (match(start, '|'))
	{
		if (match(start, '|'))
			return (add_symbol_token(OR, begin, *start, lexer));
		else
			return (add_symbol_token(PIPE, begin, *start, lexer));
	}
	else if (match(start, '('))
		return (add_symbol_token(L_PAREN, begin, *start, lexer));
	else if (match(start, ')'))
		return (add_symbol_token(R_PAREN, begin, *start, lexer));
	else
		return (set_lexer_err(lexer, UNKNOWN_SYMBOL), 0);
	return (1);
}
