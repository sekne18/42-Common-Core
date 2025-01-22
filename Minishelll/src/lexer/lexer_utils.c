/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmol <fmol@student.s19.be>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 14:18:32 by fmol              #+#    #+#             */
/*   Updated: 2025/01/14 15:26:45 by fmol             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	set_lexer_err(t_lexer *lexer, int err)
{
	lexer->err = err;
}

void	print_lexer_err(t_lexer *lexer)
{
	size_t	len;

	if (lexer->err == 0)
		return ;
	write(1, "Lexer error: ", 13);
	if (lexer->err == UNKNOWN_SYMBOL)
		write(1, "Unknown symbol:", 15);
	else if (lexer->err == DYN_ARR_ERR)
		write(1, "Dynamic array error:", 20);
	else if (lexer->err == NO_TOKENS)
		write(1, "No tokens:", 10);
	else if (lexer->err == QUOTE_ERR)
		write(1, "Unclosed quotes:", 16);
	write(1, "\nnear:\n", 7);
	len = ft_strlen(lexer->input);
	write(1, lexer->input, len);
	write(1, "\n", 1);
	len -= ft_strlen(lexer->err_occurence);
	while (len--)
		write(1, "-", 1);
	write(1, "^\n", 2);
}

int	match(char **str, char m)
{
	if (!(**str) || **str != m)
		return (0);
	(*str)++;
	return (1);
}

int	peek(char *str, char p)
{
	if (!*str || *str != p)
		return (0);
	return (1);
}
