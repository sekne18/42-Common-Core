/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_funcs.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmol <fmol@student.s19.be>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 12:46:54 by fmol              #+#    #+#             */
/*   Updated: 2025/01/15 12:57:12 by fmol             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_prompt(char *str)
{
	char	*tmp;
	char	*prompt;
	char	cwd[128];

	if (!getcwd(cwd, sizeof(cwd)))
		return (ft_strdup(BLUE "minishell$ " RESET));
	prompt = ft_strjoin(BLUE, cwd);
	if (!prompt)
		return (NULL);
	tmp = ft_strjoin(prompt, " $ ");
	free(prompt);
	if (!tmp)
		return (free(prompt), NULL);
	prompt = ft_strjoin(tmp, " " RESET);
	free(tmp);
	if (!prompt)
		return (NULL);
	if (!str)
		return (prompt);
	tmp = ft_strjoin(prompt, str);
	free(prompt);
	if (!tmp)
		return (NULL);
	return (tmp);
}

int	set_shell_var(t_context *ctx)
{
	char	cwd[128];
	char	*arg[3];

	if (!getcwd(cwd, sizeof(cwd)))
		return (free(arg[1]), 1);
	arg[1] = ft_strjoin("SHELL=", cwd);
	if (!arg[1])
		return (free(arg[1]), 1);
	arg[0] = "export";
	arg[2] = NULL;
	if (!exec_export(ctx, arg))
		return (free(arg[1]), 1);
	return (free(arg[1]), 0);
}

int	increment_shlvl(t_context *ctx)
{
	char	*arg[3];
	char	*tmp;

	arg[2] = "$SHLVL";
	arg[0] = get_var_val((const char **)(&arg[2]), ctx->envp->data, ctx);
	if (!arg[0])
		return (free(arg[0]), 1);
	arg[2] = "SHLVL=";
	if (!arg[2])
		return (free(arg[0]), 1);
	tmp = ft_itoa(ft_atoi(arg[0]) + 1);
	free(arg[0]);
	arg[1] = ft_strjoin(arg[2], tmp);
	free(tmp);
	if (!arg[1])
		return (1);
	arg[0] = "export";
	arg[2] = NULL;
	if (!exec_export(ctx, arg))
		return (free(arg[1]), 1);
	return (free(arg[1]), 0);
}
