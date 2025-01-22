/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_redir_node.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmol <fmol@student.s19.be>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 12:06:47 by fmol              #+#    #+#             */
/*   Updated: 2025/01/15 10:20:22 by fmol             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_eof_warning(const char *delim, const size_t len)
{
	ft_putstr_fd("minishell: warning: here-document delimited by EOF (wanted `",
		STDERR_FILENO);
	ft_putnstr_fd(delim, len, STDERR_FILENO);
	ft_putstr_fd("')\n", STDERR_FILENO);
}

static void	redir_err_msg(t_token *data)
{
	ft_putstr_fd("minishell: ambiguous redirect: ", STDERR_FILENO);
	ft_putnendl_fd(data->attr, data->attr_len, STDERR_FILENO);
}

static void	set_redir_flag(int type, t_context *ctx)
{
	if (type == L_REDIR || type == HEREDOC)
		ctx->redir_flag = ctx->redir_flag | IN_REDIR;
	else
		ctx->redir_flag = ctx->redir_flag | OUT_REDIR;
}

int	get_flags(int type)
{
	if (type == L_REDIR)
		return (O_RDONLY);
	else if (type == R_REDIR)
		return (O_WRONLY | O_CREAT | O_TRUNC);
	else if (type == APPEND)
		return (O_WRONLY | O_CREAT | O_APPEND);
	return (O_RDWR | O_CREAT | O_TRUNC);
}

//TODO: perror ==> 'open' should be name of file trying to open
int	exec_redir(void *data, t_context *ctx)
{
	t_tree_node	*node;
	char		*redir;
	int			fd;
	int			flags;

	node = (t_tree_node *)data;
	if (((t_token *)node->data)->flags & WILDCARD)
		return (redir_err_msg(node->data), AMBIGUOUS_REDIRECT);
	if (node->type == HEREDOC)
		redir = get_heredoc_identifier();
	else
		redir = expand_token(node->data, ctx);
	flags = get_flags(node->type);
	fd = redirect_file(redir, flags, node, ctx);
	free(redir);
	if (fd == -1)
		return (1);
	if (fd == -2)
		return (130);
	set_redir_flag(node->type, ctx);
	return (0);
}
