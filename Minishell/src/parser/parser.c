/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmol <fmol@student.s19.be>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 09:56:52 by fmol              #+#    #+#             */
/*   Updated: 2025/01/14 20:25:35 by fmol             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	match_and_or(t_parser *parser, int *op)
{
	if (match_token(parser, AND))
		*op = AND;
	else if (match_token(parser, OR))
		*op = OR;
	else
	{
		*op = 0;
		return (0);
	}
	return (1);
}

static t_tree_node	*list_chain(t_parser *parser, t_tree_node **first,
	t_tree_node **second, t_tree_node **prev)
{
	int	op;

	while (match_and_or(parser, &op))
	{
		if (!*second)
		{
			*first = create_op_node(*first, NULL, op);
			if (!*first)
				return (set_parse_err(parser, NODE_ERR), NULL);
			*prev = *first;
		}
		else
		{
			*second = create_op_node(*second, NULL, op);
			if (!*second)
				return (destroy_ast(*first, NULL),
					set_parse_err(parser, NODE_ERR), NULL);
			(*prev)->children[1] = *second;
			*prev = *second;
		}
		*second = pipeline(parser);
		if (!*second)
			return (destroy_ast(*first, NULL), NULL);
	}
	return (*first);
}

t_tree_node	*list(t_parser *parser)
{
	t_tree_node	*first;
	t_tree_node	*second;
	t_tree_node	*prev;

	first = pipeline(parser);
	if (!first)
		return (NULL);
	second = NULL;
	if (!list_chain(parser, &first, &second, &prev))
		return (NULL);
	if (second)
		prev->children[1] = second;
	return (first);
}

t_tree_node	*generate_ast(t_token_list *tokens)
{
	t_parser	parser;

	if (!tokens)
		return (NULL);
	ft_memset(&parser, 0, sizeof(t_parser));
	parser.tokens = tokens;
	parser.tree = list(&parser);
	if (parser.tokens->curr_size - 1 != parser.current)
		set_parse_err(&parser, PARSE_ERR);
	if (parser.err > 0)
		return (print_parser_err(&parser), NULL);
	return (parser.tree);
}
