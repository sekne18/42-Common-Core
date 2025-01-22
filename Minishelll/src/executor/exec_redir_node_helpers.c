/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_redir_node_helpers.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmol <fmol@student.s19.be>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 20:16:02 by fmol              #+#    #+#             */
/*   Updated: 2025/01/15 13:57:57 by fmol             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_heredoc_identifier(void)
{
	static int	i;
	char		*path;
	char		*tmp;
	char		*res;

	i = 0;
	path = getenv("TMPDIR");
	if (!path)
		path = ft_strdup("/tmp/sh-thd-");
	else
		path = ft_strjoin(path, "/sh-thd-");
	if (!path)
		return (NULL);
	tmp = ft_itoa(getpid() + i++);
	if (!tmp)
		return (free(path), NULL);
	res = ft_strjoin(path, tmp);
	free(path);
	free(tmp);
	if (!res)
		return (NULL);
	return (res);
}

static int	write_to_file(int fd, char *line, const char *delim,
		const size_t len)
{
	if (!line)
		return (print_eof_warning(delim, len), 0);
	if (ft_strlen(line) == len && !ft_strncmp(line, delim, len))
	{
		free(line);
		return (0);
	}
	write(fd, line, ft_strlen(line));
	write(fd, "\n", 1);
	free(line);
	return (1);
}

static void	read_until_delim_loop(int fd, t_token *token)
{
	char	*line;

	g_signals = g_signals | S_HEREDOC;
	while (1)
	{
		line = readline("> ");
		if (!line && g_signals & S_CTRL_C)
			break ;
		if (!write_to_file(fd, line, token->attr, token->attr_len))
			break ;
	}
	g_signals = g_signals & ~S_HEREDOC;
}

static int	read_until_delim(char *file, t_token *token, int flags,
		t_context *ctx)
{
	int		fd;
	int		tmp_fd;

	fd = open(file, flags, S_IRUSR | S_IWUSR);
	if (fd < 0)
		return (perror("minishell: open"), -1);
	dup2(ctx->std_fds[0], STDIN_FILENO);
	tmp_fd = dup(STDOUT_FILENO);
	dup2(ctx->std_fds[1], STDOUT_FILENO);
	read_until_delim_loop(fd, token);
	dup2(tmp_fd, STDOUT_FILENO);
	close(tmp_fd);
	close(fd);
	if (g_signals & S_CTRL_C)
	{
		g_signals = g_signals & ~S_CTRL_C;
		return (-2);
	}
	fd = open(file, O_RDONLY);
	if (fd < 0)
		return (perror("minishell: open"), -1);
	return (fd);
}

int	redirect_file(char *file, int flags, t_tree_node *node,
		t_context *ctx)
{
	int	fd;

	if (node->type == HEREDOC)
	{
		fd = read_until_delim(file, node->data, flags, ctx);
		if (fd <= -1)
			return (fd);
		dup2(fd, STDIN_FILENO);
		close(fd);
		unlink(file);
	}
	else
	{
		fd = open(file, flags, S_IRUSR | S_IWUSR);
		if (fd == -1)
			return (perror("minishell: open"), fd);
		if (node->type == L_REDIR)
			dup2(fd, STDIN_FILENO);
		else
			dup2(fd, STDOUT_FILENO);
		close(fd);
	}
	return (0);
}
