/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree_traversal_2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmol <fmol@student.s19.be>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 20:28:41 by fmol              #+#    #+#             */
/*   Updated: 2025/01/14 20:30:29 by fmol             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	traverse_logical_op(t_tree_node *node, int (*exec)(void *, void *),
	void *context)
{
	int	res;

	if (node->type == AND || node->type == OR)
	{
		if (node->nr_children != 2)
			return (TRAVERSE_ERR);
		res = traverse_tree(node->children[0], exec, context);
		if (res != 0)
			return (res);
		res = exec(node, context);
		if (res == LIST_STOP)
			return (0);
		else if (res != 0)
			return (res);
		res = traverse_tree(node->children[1], exec, context);
		if (res != 0)
			return (res);
		return (0);
	}
	return (TRAVERSE_ERR);
}

int	traverse_pipe(t_tree_node *node, int (*exec)(void *, void *), void *context)
{
	int	res;

	res = exec(node, context);
	if (res != 0)
		return (res);
	if (node->type == PIPE)
	{
		if (node->nr_children != 2)
			return (TRAVERSE_ERR);
		res = traverse_tree(node->children[0], exec, context);
		if (res != 0)
			return (res);
		res = exec(node, context);
		if (res != 0)
			return (res);
		res = traverse_tree(node->children[1], exec, context);
		if (res != 0)
			return (res);
		return (0);
	}
	return (TRAVERSE_ERR);
}
