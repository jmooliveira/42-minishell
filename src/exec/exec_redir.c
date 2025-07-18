/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_redir.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ancarol9 <ancarol9@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 01:41:43 by ancarol9          #+#    #+#             */
/*   Updated: 2025/07/18 01:53:52 by ancarol9         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	exec_redir_in(t_redir *r, t_data *data)
{
	int	fd;

	if (!r->filename || r->filename[0] == '\0')
		return (print_redir_error(r->filename, data));
	fd = open(r->filename, O_RDONLY);
	if (fd == -1)
		return (print_redir_error(r->filename, data));
	if (dup2(fd, STDIN_FILENO) == -1)
	{
		close(fd);
		return (print_redir_error("dup2", data));
	}
	close(fd);
	return (0);
}

int	exec_redir_out(t_redir *r, t_data *data)
{
	int	fd;

	if (!r->filename || r->filename[0] == '\0')
		return (print_redir_error(r->filename, data));
	fd = open(r->filename, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (fd == -1)
		return (print_redir_error(r->filename, data));
	if (dup2(fd, STDOUT_FILENO) == -1)
	{
		close(fd);
		return (print_redir_error("dup2", data));
	}
	close(fd);
	return (0);
}

int	exec_append(t_redir *r, t_data *data)
{
	int	fd;

	if (!r->filename || r->filename[0] == '\0')
		return (print_redir_error(r->filename, data));
	fd = open(r->filename, O_CREAT | O_WRONLY | O_APPEND, 0644);
	if (fd == -1)
		return (print_redir_error(r->filename, data));
	if (dup2(fd, STDOUT_FILENO) == -1)
	{
		close(fd);
		return (print_redir_error("dup2", data));
	}
	close(fd);
	return (0);
}

static int	apply_redir(t_redir *redir, t_data *data)
{
	int		ret;
	t_redir	*r;

	r = redir;
	while (r)
	{
		if (r->type == REDIR_IN)
			ret = exec_redir_in(r, data);
		else if (r->type == REDIR_OUT)
			ret = exec_redir_out(r, data);
		else if (r->type == APPEND)
			ret = exec_append(r, data);
		else if (r->type == HEREDOC)
			ret = exec_redir_in(r, data);
		else
			ret = 0;
		if (ret != 0)
			return (ret);
		r = r->next;
	}
	return (0);
}

int	execute_redir(t_ast *node, t_data *data)
{
	int	status;

	data->fd_bk[0] = dup(STDIN_FILENO);
	data->fd_bk[1] = dup(STDOUT_FILENO);
	if (data->fd_bk[0] == -1 || data->fd_bk[1] == -1)
	{
		data->exit_status = 130;
		return (130);
	}
	status = apply_redir(node->redir, data);
	if (status != 0)
	{
		restore_fds(data);
		return (status);
	}
	if (node->left)
		status = exec_ast(node->left, data);
	else if (node->args && node->args[0])
		status = exec_cmd(node, data);
	restore_fds(data);
	cleanup_heredoc_files(node->redir);
	data->exit_status = status;
	return (status);
}
