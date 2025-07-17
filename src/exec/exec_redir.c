/*exec_redir.c*/

#include "../../include/minishell.h"

int	print_redir_error(char *filename, t_data *data)
{
    ft_putstr_fd("minishell: ", STDERR_FILENO);
    ft_putstr_fd(filename, STDERR_FILENO);
    ft_putstr_fd(": ", STDERR_FILENO);
    perror("");
    if (data)
        data->exit_status = 1;
    return (1);
}

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
    int         ret;
    t_redir     *r;

    r = redir;
    while (r)
    {
        if (r->type == REDIR_IN)
            ret = exec_redir_in(r, data);
        else if (r->type == REDIR_OUT)
            ret = exec_redir_out(r, data);
        else if (r->type == APPEND)
            ret = exec_append(r,data);
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

void	restore_fds(t_data *data)
{
	dup2(data->fd_bk[0], STDIN_FILENO);
	dup2(data->fd_bk[1], STDOUT_FILENO);
	close(data->fd_bk[0]);
	close(data->fd_bk[1]);
}

void    cleanup_heredoc_files(t_redir *r)
{
    while (r)
    {
    	if (r->type == HEREDOC && r->filename)
    		unlink(r->filename);
    	r = r->next;
    }
}

int     execute_redir(t_ast *node, t_data *data)
{
    int         status;
    
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
