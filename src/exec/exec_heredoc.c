/*exec_heredoc.c*/

#include "../../include/minishell.h"

int	preprocess_heredoc(t_ast *node)
{
	t_redir	*r;

	if (!node)
		return (0);
	if (node->redir)
	{
		r = node->redir;
		while (r)
		{
			if (r->type == HEREDOC)
				exec_heredoc(r);
			r = r->next;
		}
	}
	preprocess_heredoc(node->left);
	preprocess_heredoc(node->right);
	return (0);
}

int	exec_heredoc(t_redir *r)
{
	int		fd;
	char	*line;

	if (r->hd_written)
		return (0);
	fd = open (r->filename, O_CREAT | O_WRONLY | O_TRUNC, 0600);
	if (fd == -1)
		return (perror(r->filename), 1);
	heredoc_signal();
	while (42)
	{
		line = readline("> ");
		if (!line)
		{
			free(line);
			return (130);
		}
		if (ft_strncmp(line, r->delim, ft_strlen(r->delim) + 1) == 0)
		{
			free(line);
			break ;
		}
		write(fd, line, ft_strlen(line));
		write(fd, "\n", 1);
		free(line);
	}
	free(line);
	close(fd);
	r->hd_written = true;
	interactive_signal();
	return (0);
}
