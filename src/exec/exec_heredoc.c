/*exec_heredoc.c*/

#include "../../include/minishell.h"

int     exec_heredoc(char *filename, char *delim)
{
	int     fd;
	char    *line;

	g_signal = 0;
	fd = open (filename, O_CREAT | O_WRONLY | O_TRUNC, 0600);
	if (fd == -1)
		return (perror(filename), 1);
	heredoc_signal();
	while (42)
	{
		line = readline("> ");
		if (!line)
		{
			if (g_signal == SIGINT)
			{
				close(fd);
				return (130);
			}
			ft_putstr_fd("minishell: warning: here-document delimited by end-of-file (wanted `", 2);
			ft_putstr_fd(delim, 2);
			ft_putendl_fd("')", 2);
			break;
		}
		if (ft_strncmp(line, delim, ft_strlen(delim) + 1) == 0)
		{
			break ;
		}
		write(fd, line, ft_strlen(line));
		write(fd, "\n", 1);
		free(line);
	}
	free(line);
	close(fd);
	interactive_signal();
	return (0);
}
