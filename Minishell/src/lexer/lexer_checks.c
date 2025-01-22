/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_checks.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmol <fmol@student.s19.be>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 14:20:22 by fmol              #+#    #+#             */
/*   Updated: 2025/01/14 15:27:55 by fmol             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_whitespace(char c)
{
	return (c == ' ' || (c >= '\t' && c <= '\r'));
}

int	is_reserved_symbol(char c)
{
	return (c == '|' || c == '<' || c == '>' || c == '(' || c == ')'
		|| c == '&' || c == '|');
}

int	is_identifier_char(char c, int flags)
{
	if ((!(flags & QUOTE || flags & D_QUOTE)
			&& (is_whitespace(c) || is_reserved_symbol(c)))
		|| c == '\'' || c == '"')
		return (0);
	if (c >= ' ' && c <= 126)
		return (1);
	return (0);
}
