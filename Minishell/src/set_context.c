/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_context.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmol <fmol@student.s19.be>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/04 22:12:11 by jans              #+#    #+#             */
/*   Updated: 2025/01/15 14:03:21 by fmol             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	destroy_context(t_context *context)
{
	close(context->std_fds[0]);
	close(context->std_fds[1]);
	destroy_dyn_arr(context->envp, free);
	destroy_dyn_arr(context->args, free);
	destroy_dyn_arr(context->pids, NULL);
	destroy_dyn_arr(context->tokens, NULL);
	destroy_ast(context->ast, NULL);
	if (context->input)
		free(context->input);
	free(context);
}

void	set_context(t_context *context, char **envp)
{
	context->std_fds[0] = dup(STDIN_FILENO);
	context->std_fds[1] = dup(STDOUT_FILENO);
	context->redir_flag = NONE;
	context->pipe_flag = NONE;
	context->last_exit_status = 0;
	context->envp = create_duplicate_envp(envp);
	context->args = new_dyn_arr(1, sizeof(char *));
	context->pids = new_dyn_arr(1, sizeof(t_cmd_status));
	if (!context->envp || !context->args || !context->pids)
	{
		destroy_dyn_arr(context->envp, free);
		destroy_dyn_arr(context->args, free);
		destroy_dyn_arr(context->pids, NULL);
		exit(1);
	}
}

void	reset_context(t_context *context)
{
	g_signals = 0;
	destroy_dyn_arr(context->tokens, NULL);
	context->tokens = NULL;
	destroy_ast(context->ast, NULL);
	context->ast = NULL;
	if (context->input)
		free(context->input);
	context->input = NULL;
	dup2(context->std_fds[0], STDIN_FILENO);
	dup2(context->std_fds[1], STDOUT_FILENO);
	context->redir_flag = NONE;
	context->pipe_flag = NONE;
}

void	*create_duplicate_envp(char **envp)
{
	int			i;
	t_dyn_arr	*dyn_arr;
	char		*curr_env;

	dyn_arr = new_dyn_arr(1, sizeof(char *));
	if (!dyn_arr)
		return (NULL);
	i = -1;
	while (envp[++i])
	{
		curr_env = ft_strdup(envp[i]);
		if (((t_dyn_arr *)dyn_arr)->curr_size == 0)
			push_back(dyn_arr, &curr_env);
		else
			replace(dyn_arr, &curr_env, i, free);
		push_back(dyn_arr, NULL);
	}
	return (dyn_arr);
}
