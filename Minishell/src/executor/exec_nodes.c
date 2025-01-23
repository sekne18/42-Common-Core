/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_nodes.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmol <fmol@student.s19.be>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 12:01:37 by fmol              #+#    #+#             */
/*   Updated: 2025/01/15 11:28:11 by fmol             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	exec_pipe(void *data, t_context *ctx)
{
	(void)data;
	if (ctx->pipe_flag == NONE)
	{
		if (pipe(ctx->pipe_fds) == -1)
		{
			perror("pipe");
			return (1);
		}
		dup2(ctx->pipe_fds[1], STDOUT_FILENO);
		close(ctx->pipe_fds[1]);
	}
	else if (ctx->pipe_flag == LEFT && !ctx->cmd_flag)
	{
		dup2(ctx->pipe_fds[1], STDOUT_FILENO);
		close(ctx->pipe_fds[1]);
	}
	if (ctx->pipe_flag == NONE)
	{
		ctx->redir_flag |= IN;
		ctx->pipe_flag = LEFT;
	}
	else if (ctx->pipe_flag == LEFT)
		ctx->pipe_flag = NONE;
	return (0);
}

int	exec_list(void *data, t_context *ctx)
{
	t_tree_node	*token;

	token = (t_tree_node *)data;
	handle_cmd_status(ctx);
	if (token->type == AND && ctx->last_exit_status != 0)
		return (LIST_STOP);
	else if (token->type == OR && ctx->last_exit_status == 0)
		return (LIST_STOP);
	else if (token->type != AND && token->type != OR)
		return (TRAVERSE_ERR);
	return (0);
}

int	exec_node(void *data, void *context)
{
	t_tree_node	*node;

	node = (t_tree_node *)data;
	if (node->type == CMD)
		return (exec_cmd(node->data, context));
	else if (node->type == ARG)
		return (exec_args(node->data, context));
	else if (node->type == PIPE)
		return (exec_pipe(node->data, context));
	else if (node->type == L_REDIR || node->type == R_REDIR
		|| node->type == APPEND || node->type == HEREDOC)
		return (exec_redir(node, context));
	else if (node->type == AND || node->type == OR)
		return (exec_list(node, context));
	return (TRAVERSE_ERR);
}
