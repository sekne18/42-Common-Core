/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmol <fmol@student.s19.be>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 11:23:42 by fmol              #+#    #+#             */
/*   Updated: 2025/01/15 13:10:39 by fmol             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_signals = 0;

void	print_exec_err(int err)
{
	char	*err_msg;

	if (err == FORK_ERR)
		err_msg = "fork failed";
	else if (err == MALLOC_ERR)
		err_msg = "malloc error";
	else if (err == STATUS_DYN_ARR_ERR)
		err_msg = "malloc error";
	else
		err_msg = "unknown error";
	ft_putstr_fd("minishell: fatal error during execution: ", STDERR_FILENO);
	ft_putstr_fd(err_msg, STDERR_FILENO);
}

//action = 0 <> nothing, 1 <> exit, 2 <> continue
static int	read_input(t_context *ctx, int *action)
{
	char	*prompt;

	*action = 1;
	prompt = get_prompt(NULL);
	if (!prompt)
		return (print_exec_err(MALLOC_ERR), 1);
	ctx->input = readline(prompt);
	free(prompt);
	if (!ctx->input)
		return (0);
	if (*ctx->input == '\0')
	{
		reset_context(ctx);
		*action = 2;
		return (0);
	}
	*action = 0;
	return (0);
}

static int	process_input(t_context *ctx, int *action)
{
	int	status;

	*action = 0;
	ctx->tokens = scan_input(ctx->input);
	ctx->ast = generate_ast(ctx->tokens);
	if (!ctx->ast)
	{
		reset_context(ctx);
		ctx->last_exit_status = 2;
		*action = 2;
		return (0);
	}
	if (*ctx->input)
		add_history(ctx->input);
	status = execute(ctx->ast, ctx);
	if (status != 0)
	{
		*action = 1;
		if (status == 2)
			return (get_status(ctx->args->data));
		return (print_exec_err(status), 1);
	}
	return (0);
}

int	main(int argc, char **argv, char **envp)
{
	t_context	*context;
	int			status;
	int			action;

	context = ft_calloc(1, sizeof(t_context));
	if (!context)
		return ((void)argc, (void)argv, 1);
	set_context(context, envp);
	if (!increment_shlvl(context) || !set_shell_var(context))
		return (destroy_context(context), 1);
	setup_signals();
	while (1)
	{
		status = read_input(context, &action);
		if (action == 0)
			status = process_input(context, &action);
		if (action == 1)
			return (destroy_context(context), status);
		if (action != 2 && (!context->input || context->last_exit_status == -1))
			break ;
		reset_context(context);
	}
	destroy_context(context);
	return (0);
}
