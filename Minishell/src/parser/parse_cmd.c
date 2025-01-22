/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmol <fmol@student.s19.be>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 13:16:57 by fmol              #+#    #+#             */
/*   Updated: 2025/01/15 14:38:50 by fmol             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_tree_node	*redirect(t_parser *parser)
{
	t_tree_node	*node;
	int			op;

	op = 0;
	if (match_token(parser, L_REDIR))
		op = L_REDIR;
	else if (match_token(parser, R_REDIR))
		op = R_REDIR;
	else if (match_token(parser, APPEND))
		op = APPEND;
	else if (match_token(parser, HEREDOC))
		op = HEREDOC;
	else
		return (NULL);
	if (!peek_token(parser, IDENTIFIER))
		return (set_parse_err(parser, PARSE_ERR), NULL);
	node = create_id_node(parser, op);
	if (!node)
		return (set_parse_err(parser, NODE_ERR), NULL);
	return (node);
}

static t_tree_node	*basic_cmd_helper(t_parser *parser, int *cmd_flag,
		t_tree_node **prev, t_tree_node **node)
{
	*prev = redirect(parser);
	if (!*prev && parser->err)
		return (destroy_ast(*node, NULL), NULL);
	else if (!*prev && !parser->err && peek_token(parser, IDENTIFIER))
	{
		*prev = create_id_node(parser, *cmd_flag);
		*cmd_flag = ARG;
		if (!*prev)
			return (destroy_ast(*node, NULL), set_parse_err(parser,
					NODE_ERR), NULL);
	}
	else if (!*prev)
		return (NULL);
	if (!*node)
		*node = *prev;
	else
		*node = link_basic_cmd_nodes(*node, *prev);
	if (!*node)
		return (set_parse_err(parser, NODE_ERR), NULL);
	*prev = NULL;
	return (*node);
}

t_tree_node	*basic_cmd(t_parser *parser)
{
	t_tree_node	*node;
	t_tree_node	*tmp;
	int			cmd_flag;

	cmd_flag = CMD;
	node = NULL;
	tmp = NULL;
	while (1)
		if (!basic_cmd_helper(parser, &cmd_flag, &tmp, &node))
			break ;
	if (parser->err)
		return (NULL);
	if (!node)
		return (set_parse_err(parser, PARSE_ERR), NULL);
	return (node);
}

t_tree_node	*command(t_parser *parser)
{
	t_tree_node	*node;

	if (match_token(parser, L_PAREN))
	{
		node = list(parser);
		if (!node)
			return (NULL);
		if (!match_token(parser, R_PAREN))
			return (destroy_ast(node, NULL), set_parse_err(parser, PARSE_ERR),
				NULL);
		return (node);
	}
	return (basic_cmd(parser));
}
