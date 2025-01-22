/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_pipeline.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmol <fmol@student.s19.be>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 20:25:48 by fmol              #+#    #+#             */
/*   Updated: 2025/01/14 20:30:15 by fmol             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_tree_node	*pipeline_chain(t_parser *parser, t_tree_node **first,
	t_tree_node **second, t_tree_node **prev)
{
	while (match_token(parser, PIPE))
	{
		if (!*second)
		{
			*first = create_op_node(*first, NULL, PIPE);
			if (!*first)
				return (set_parse_err(parser, NODE_ERR), NULL);
			*prev = *first;
		}
		else
		{
			*second = create_op_node(*second, NULL, PIPE);
			if (!*second)
				return (destroy_ast(*first, NULL),
					set_parse_err(parser, NODE_ERR), NULL);
			(*prev)->children[1] = *second;
			*prev = *second;
		}
		*second = command(parser);
		if (!*second)
			return (destroy_ast(*first, NULL), NULL);
	}
	return (*first);
}

t_tree_node	*pipeline(t_parser *parser)
{
	t_tree_node	*first;
	t_tree_node	*second;
	t_tree_node	*prev;

	first = command(parser);
	if (!first)
		return (NULL);
	second = NULL;
	if (!pipeline_chain(parser, &first, &second, &prev))
		return (NULL);
	if (second)
		prev->children[1] = second;
	return (first);
}
