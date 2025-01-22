/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmol <fmol@student.s19.be>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 12:17:21 by fmol              #+#    #+#             */
/*   Updated: 2025/01/14 20:24:15 by fmol             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	handle_cmd_status(t_context *context)
{
	size_t	i;
	int		status;

	i = 0;
	while (i < context->pids->curr_size)
	{
		if (((t_cmd_status *)get_val(context->pids, i))->type == EXTERNAL)
		{
			waitpid(((t_cmd_status *)get_val(context->pids, i))->u_value.pid,
				&status, 0);
			if (WIFEXITED(status))
				context->last_exit_status = WEXITSTATUS(status);
			else if (WIFSIGNALED(status))
				context->last_exit_status = 128 + WTERMSIG(status);
			else
				context->last_exit_status = 1;
		}
		else
			context->last_exit_status = ((t_cmd_status *)get_val(context->pids,
						i))->u_value.status;
		i++;
	}
	clear_dyn_arr(context->pids, NULL);
	return (1);
}

static void	clear_pids_array(t_context *ctx)
{
	size_t	i;

	i = 0;
	while (i < ctx->pids->curr_size)
	{
		if (((t_cmd_status *)get_val(ctx->pids, i))->type == EXTERNAL)
			waitpid(((t_cmd_status *)get_val(ctx->pids,
						i))->u_value.pid, NULL, 0);
		i++;
	}
	destroy_dyn_arr(ctx->pids, NULL);
}

int	execute(t_tree_node *ast, t_context *context)
{
	int	exec_res;

	if (!ast)
		return (0);
	exec_res = traverse_tree(ast, exec_node, context);
	if (exec_res == LIST_STOP)
		return (0);
	if (exec_res == EXIT)
		return (2);
	else if (exec_res == TRAVERSE_ERR || exec_res == MALLOC_ERR
		|| exec_res == DYN_ARR_ERR || exec_res == FORK_ERR)
		return (1);
	else if (exec_res == AMBIGUOUS_REDIRECT)
		return (0);
	else if (exec_res == STATUS_DYN_ARR_ERR)
		return (clear_pids_array(context), 1);
	else if (exec_res == 130)
	{
		context->last_exit_status = 130;
		return (0);
	}
	handle_cmd_status(context);
	return (0);
}
