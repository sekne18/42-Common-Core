/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmol <fmol@student.s19.be>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 14:40:52 by fmol              #+#    #+#             */
/*   Updated: 2025/01/14 15:28:51 by fmol             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*scan_token(char *curr, t_lexer *lexer)
{
	while (is_whitespace(*curr))
		curr++;
	if (!*curr)
		return (curr);
	if (!lexer->err && match_keywords(&curr, lexer))
		return (curr);
	if (!lexer->err && match_symbols(&curr, lexer))
		return (curr);
	if (!lexer->err)
		return (curr);
	return (NULL);
}

static t_token_list	*get_final_tokens(t_lexer *lexer)
{
	t_token	token;

	if (lexer->err > 0)
		return (destroy_dyn_arr(lexer->list, NULL), print_lexer_err(lexer),
			NULL);
	init_token(&token, EOF, NULL, 0);
	if (!push_back(lexer->list, &token))
		return (set_lexer_err(lexer, DYN_ARR_ERR),
			destroy_dyn_arr(lexer->list, NULL),
			print_lexer_err(lexer), NULL);
	return (lexer->list);
}

t_token_list	*scan_input(char *str)
{
	t_lexer	lexer;
	char	*ptr;

	if (!str)
		return (NULL);
	ft_memset(&lexer, 0, sizeof(t_lexer));
	lexer.input = str;
	lexer.list = new_dyn_arr(1, sizeof(t_token));
	if (!lexer.list)
		return (set_lexer_err(&lexer, DYN_ARR_ERR), NULL);
	ptr = str;
	while (*ptr != '\0')
	{
		ptr = scan_token(ptr, &lexer);
		if (!ptr)
			break ;
	}
	if (!lexer.err && lexer.list->curr_size == 0)
		set_lexer_err(&lexer, NO_TOKENS);
	return (get_final_tokens(&lexer));
}
