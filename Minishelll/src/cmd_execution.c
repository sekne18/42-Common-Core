/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_execution.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmol <fmol@student.s19.be>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 15:23:25 by jsekne            #+#    #+#             */
/*   Updated: 2025/01/15 10:31:15 by fmol             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_builtin(char *cmd)
{
	if (!ft_strcmp(cmd, "echo") || !ft_strcmp(cmd, "cd")
		|| !ft_strcmp(cmd, "pwd") || !ft_strcmp(cmd, "export")
		|| !ft_strcmp(cmd, "unset") || !ft_strcmp(cmd, "env")
		|| !ft_strcmp(cmd, "exit"))
		return (1);
	return (0);
}

int	builtin(void *data, t_context *context)
{
	int		return_code;
	char	**args;

	args = (char **)data;
	return_code = 1;
	if (!ft_strcmp(args[0], "cd"))
		return_code = exec_cd(data);
	else if (!ft_strcmp(args[0], "echo"))
		return_code = exec_echo(data);
	else if (!ft_strcmp(args[0], "pwd"))
		return_code = exec_pwd();
	else if (!ft_strcmp(args[0], "export"))
		return_code = exec_export(context, data);
	else if (!ft_strcmp(args[0], "unset"))
		return_code = exec_unset(context->envp, data);
	else if (!ft_strcmp(args[0], "env"))
		return_code = exec_env(context->envp->data, args[1]);
	return (return_code);
}

//TODO: what should the final exit status be?
int	handle_child_process(char **data, t_context *ctx)
{
	if (!add_path(&(data[0]), ((char **)ctx->envp->data)))
	{
		ft_putstr_fd("command not found: ", STDERR_FILENO);
		ft_putendl_fd(data[0], STDERR_FILENO);
		destroy_context(ctx);
		exit(127);
	}
	if (execve(data[0], data, ((char **)ctx->envp->data)) == -1)
	{
		perror("execve");
		destroy_context(ctx);
		exit(126);
	}
	destroy_context(ctx);
	exit(1);
}

int	external_command(void *data, t_context *context)
{
	pid_t	pid;

	pid = fork();
	if (pid == 0)
	{
		reset_signals_in_child();
		close(context->std_fds[0]);
		close(context->std_fds[1]);
		if (context->redir_flag & IN)
			close(context->pipe_fds[0]);
		return (handle_child_process(data, context));
	}
	else if (pid < 0)
		perror("fork");
	return (pid);
}
