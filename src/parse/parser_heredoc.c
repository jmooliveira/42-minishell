#include "../../include/minishell.h"

static void	print_eof_warning(char *delim)
{
	ft_putstr_fd("minishell: warning: here-document delimited by end-of-file (wanted `", 2);
	ft_putstr_fd(delim, 2);
	ft_putendl_fd("')", 2);
}

static int	handle_line(int fd, char *line, char *delim)
{
	if (ft_strncmp(line, delim, ft_strlen(delim) + 1) == 0)
		return (1);
	write(fd, line, ft_strlen(line));
	write(fd, "\n", 1);
	return (0);
}

int	exec_heredoc(char *filename, char *delim)
{
	int		fd;
	char	*line;

	g_signal = 0;
	fd = open(filename, O_CREAT | O_WRONLY | O_TRUNC, 0600);
	if (fd == -1)
		return (print_redir_error(filename, NULL));
	heredoc_signal();
	while (42)
	{
		line = readline("> ");
		if (!line)
		{
			if (g_signal == SIGINT)
				return (close(fd), 130);
			print_eof_warning(delim);
			break ;
		}
		if (handle_line(fd, line, delim))
			break ;
		free(line);
	}
	free(line);
	close(fd);
	interactive_signal();
	return (0);
}
