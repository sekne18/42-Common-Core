/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree_traversal.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmol <fmol@student.s19.be>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 12:19:13 by fmol              #+#    #+#             */
/*   Updated: 2025/01/14 20:29:02 by fmol             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	gather_args(t_tree_node *node, int (*exec)(void *, void *), void *context)
{
	int	res;

	res = exec(node, context);
	if (res != 0)
		return (res);
	while (node->nr_children)
	{
		res = exec(node->children[0], context);
		if (res != 0)
			return (res);
		node = node->children[0];
	}
	return (0);
}

int	traverse_cmd(t_tree_node *node, int (*exec)(void *, void *), void *context)
{
	int	res;

	if (node->type == CMD)
	{
		if (node->nr_children > 0)
		{
			res = gather_args(node->children[0], exec, context);
			if (res != 0)
				return (res);
		}
		res = exec(node, context);
		if (res != 0)
			return (res);
		return (0);
	}
	return (TRAVERSE_ERR);
}

int	traverse_redir(t_tree_node *node, int (*exec)(void *, void *),
	void *context)
{
	int	res;

	if (node->type == L_REDIR || node->type == R_REDIR
		|| node->type == APPEND || node->type == HEREDOC)
	{
		res = exec(node, context);
		if (res != 0)
			return (res);
		if (!node->nr_children)
			return (0);
		else if (node->children[0]->type == CMD)
			return (traverse_tree(node->children[0], exec, context));
		res = gather_args(node->children[0], exec, context);
		if (res != 0)
			return (res);
		if (node->nr_children == 1)
			return (0);
		res = traverse_tree(node->children[1], exec, context);
		if (res != 0)
			return (res);
		return (0);
	}
	return (TRAVERSE_ERR);
}

int	traverse_tree(t_tree_node *node, int (*exec)(void *, void *), void *context)
{
	if (!node)
		return (0);
	else if (node->type == AND || node->type == OR)
		return (traverse_logical_op(node, exec, context));
	else if (node->type == PIPE)
		return (traverse_pipe(node, exec, context));
	else if (node->type == CMD)
		return (traverse_cmd(node, exec, context));
	else if (node->type == L_REDIR || node->type == R_REDIR
		|| node->type == APPEND || node->type == HEREDOC)
		return (traverse_redir(node, exec, context));
	return (TRAVERSE_ERR);
}
