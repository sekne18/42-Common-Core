/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmol <fmol@student.s19.be>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 11:17:32 by fmol              #+#    #+#             */
/*   Updated: 2025/01/15 09:25:43 by fmol             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	start_cmd(t_context *ctx)
{
	t_cmd_status	status;

	ft_memset(&status, 0, sizeof(t_cmd_status));
	if (is_builtin(((char **)ctx->args->data)[0]))
	{
		if (!ft_strcmp(((char **)ctx->args->data)[0], "exit"))
			return (EXIT);
		status.type = BUILTIN;
		status.u_value.status = builtin(ctx->args->data, ctx);
	}
	else
	{
		status.type = EXTERNAL;
		status.u_value.pid = external_command(ctx->args->data, ctx);
		if (status.u_value.pid < 0)
			return (FORK_ERR);
	}
	if (!push_back(ctx->pids, &status))
		return (STATUS_DYN_ARR_ERR);
	return (0);
}

void	set_fds(t_context *ctx)
{
	dup2(ctx->std_fds[0], STDIN_FILENO);
	dup2(ctx->std_fds[1], STDOUT_FILENO);
	if (ctx->redir_flag & OUT)
		ctx->redir_flag = (ctx->redir_flag & ~OUT);
	if (ctx->redir_flag & IN)
	{
		ctx->redir_flag = (ctx->redir_flag & ~IN) | OUT;
		ctx->tmp_fd = ctx->pipe_fds[0];
	}
	if (ctx->redir_flag & OUT_REDIR)
		ctx->redir_flag = (ctx->redir_flag & ~OUT_REDIR);
	if (ctx->redir_flag & IN_REDIR)
		ctx->redir_flag = (ctx->redir_flag & ~IN_REDIR);
}

static int	apply_wildcard(t_token *token, char **cmd)
{
	char	**tmp_split;
	size_t	i;

	if (!(token->flags & WILDCARD))
		return (1);
	*cmd = expand_wildcard(*cmd);
	if (!*cmd)
		return (MALLOC_ERR);
	tmp_split = ft_split(*cmd, ' ');
	free(*cmd);
	if (!tmp_split)
		return (0);
	*cmd = tmp_split[0];
	i = 0;
	while (tmp_split[++i])
		free(tmp_split[i]);
	free(tmp_split);
	return (1);
}

/*
 * 0) context will have a dup of STDIN and STDOUT at the start of minishell
 * 1) STDIN and STDOUT are replaced  in pipe and redir nodes in parent
 * 1.1) STDIN cannot be replaced immediately in pipe node since the STDIN of the
 * next command is not yet known so we save the read end of the pipe in
 * ctx->tmp_fd and set the redir_flag to IN after the write end of the pipe cmd
 * is executed we will set the redir_flag to OUT cmds will check the redir_flag
 * to see whether STDIN should be replaced with the read end of the pipe 1.2)
 * make sure all necessary fds are closed in the child process 2) in exec_cmd,
 * after we have forked, we will reset STDIN and STDOUT to the duped fds in the
 * parent
 */
int	exec_cmd(void *data, t_context *ctx)
{
	char	*cmd;
	int		status;

	cmd = expand_token(data, ctx);
	if (!cmd || !apply_wildcard(data, &cmd))
		return (MALLOC_ERR);
	if ((ctx->args->curr_size == 0 && !push_back(ctx->args, NULL))
		|| !replace(ctx->args, &cmd, 0, free)
		|| !push_back(ctx->args, NULL))
		return (DYN_ARR_ERR);
	if (ctx->redir_flag & OUT && !(ctx->redir_flag & IN_REDIR))
	{
		dup2(ctx->tmp_fd, STDIN_FILENO);
		close(ctx->tmp_fd);
	}
	status = start_cmd(ctx);
	if (status)
		return (status);
	set_fds(ctx);
	clear_dyn_arr(ctx->args, free);
	ctx->cmd_flag = 1;
	return (0);
}
