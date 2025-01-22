/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_nodes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmol <fmol@student.s19.be>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 12:20:09 by fmol              #+#    #+#             */
/*   Updated: 2025/01/14 14:22:23 by fmol             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_tree_node	*create_id_node(t_parser *parser, int type)
{
	t_tree_node	*node;
	t_token		*token;

	node = malloc(sizeof(t_tree_node));
	if (!node)
		return (NULL);
	token = match_token(parser, IDENTIFIER);
	if (!token)
		return (free(node), NULL);
	node->type = type;
	node->data = token;
	node->nr_children = 0;
	node->children = NULL;
	return (node);
}

t_tree_node	*create_redirect_node(t_parser *parser, int op)
{
	t_tree_node	*node;
	t_token		*token;

	node = malloc(sizeof(t_tree_node));
	if (!node)
		return (NULL);
	token = match_token(parser, IDENTIFIER);
	if (!token)
		return (free(node), NULL);
	node->type = op;
	node->data = token;
	node->nr_children = 0;
	node->children = NULL;
	return (node);
}

t_tree_node	*create_op_node(t_tree_node *first, t_tree_node *second, int op)
{
	t_tree_node	*node;

	node = malloc(sizeof(t_tree_node));
	if (!node)
		return (destroy_ast(first, NULL), destroy_ast(second, NULL), NULL);
	node->children = malloc(sizeof(t_tree_node *) * 2);
	if (!node->children)
		return (destroy_ast(first, NULL), destroy_ast(second, NULL), free(node),
			NULL);
	node->type = op;
	node->children[0] = first;
	node->children[1] = second;
	node->nr_children = 2;
	node->data = NULL;
	return (node);
}
