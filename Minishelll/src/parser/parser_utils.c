/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmol <fmol@student.s19.be>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 13:10:06 by fmol              #+#    #+#             */
/*   Updated: 2025/01/14 14:40:23 by fmol             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_parser_err(t_parser *parser)
{
	t_token	*token;

	if (parser->err == 0)
		return ;
	write(1, "minishell: ", 11);
	if (parser->err == PARSE_ERR)
		write(1, "syntax error near \'", 19);
	else if (parser->err == NODE_ERR)
		write(1, "malloc error near \'", 15);
	token = get_val(parser->tokens, parser->err_occurence);
	if (token->type == EOF)
		write(1, "newline\'\n", 9);
	else
	{
		write(1, token->attr, token->attr_len);
		write(1, "\'\n", 2);
	}
}

void	set_parse_err(t_parser *parser, int err)
{
	parser->err = err;
	parser->err_occurence = parser->current;
}

t_token	*peek_token(t_parser *parser, int type)
{
	t_token	*token;

	token = get_val(parser->tokens, parser->current);
	if (token->type == type)
		return (token);
	return (NULL);
}

t_token	*match_token(t_parser *parser, int type)
{
	t_token	*token;

	token = get_val(parser->tokens, parser->current);
	if (token->type == type)
	{
		parser->current++;
		return (token);
	}
	return (NULL);
}

void	destroy_ast(t_tree_node *node, void (*destroy_data)(void *))
{
	size_t	i;

	if (!node)
		return ;
	i = 0;
	while (i < node->nr_children)
	{
		destroy_ast(node->children[i], destroy_data);
		i++;
	}
	if (destroy_data)
		destroy_data(node->data);
	free(node->children);
	free(node);
}
