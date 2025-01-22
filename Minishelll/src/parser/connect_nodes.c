/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   connect_nodes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmol <fmol@student.s19.be>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 12:21:29 by fmol              #+#    #+#             */
/*   Updated: 2025/01/14 14:22:07 by fmol             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_redir_node(t_tree_node *node)
{
	return (node->type == L_REDIR || node->type == R_REDIR
		|| node->type == APPEND || node->type == HEREDOC);
}

static int	realloc_children_arr(t_tree_node *node, size_t newsize)
{
	t_tree_node	**added_children;

	added_children = malloc(sizeof(t_tree_node *) * (newsize));
	if (!added_children)
		return (0);
	ft_memcpy(added_children, node->children, sizeof(t_tree_node *)
		* node->nr_children);
	free(node->children);
	node->children = added_children;
	return (1);
}

static int	insert_left(t_tree_node *root, t_tree_node *new)
{
	while (root->nr_children > 0 && is_redir_node(root->children[0]))
		root = root->children[0];
	if (!root->nr_children)
		root->children = malloc(sizeof(t_tree_node *));
	else
	{
		if (!realloc_children_arr(root, root->nr_children + 1))
			return (0);
		ft_memmove(root->children + 1, root->children, sizeof(t_tree_node *)
			* root->nr_children);
	}
	if (!root->children)
		return (0);
	root->children[0] = new;
	root->nr_children++;
	return (1);
}

static int	insert_right(t_tree_node *root, t_tree_node *new)
{
	while (root->nr_children > 1
		|| (root->nr_children == 1 && !is_redir_node(root->children[0])))
		root = root->children[root->nr_children - 1];
	if (!realloc_children_arr(root, root->nr_children + 1))
		return (0);
	root->children[root->nr_children] = new;
	root->nr_children++;
	return (1);
}

t_tree_node	*link_basic_cmd_nodes(t_tree_node *root, t_tree_node *new)
{
	if (is_redir_node(root) && !is_redir_node(new))
	{
		if (!insert_right(root, new))
			return (destroy_ast(root, NULL), destroy_ast(new, NULL), NULL);
	}
	else if (is_redir_node(root) && is_redir_node(new))
	{
		if (!insert_left(root, new))
			return (destroy_ast(root, NULL), destroy_ast(new, NULL), NULL);
	}
	else if (!is_redir_node(root) && !is_redir_node(new))
	{
		if (!insert_right(root, new))
			return (destroy_ast(root, NULL), destroy_ast(new, NULL), NULL);
	}
	else
	{
		if (!insert_right(new, root))
			return (destroy_ast(root, NULL), destroy_ast(new, NULL), NULL);
		root = new;
	}
	return (root);
}
